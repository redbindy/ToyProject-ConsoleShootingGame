#define _CRT_SECURE_NO_WARNINGS

#include "GameManager.h"

namespace ConsoleShootingGame
{
    GameManager* GameManager::s_instance = nullptr;

    void GameManager::CreateInstance(const HANDLE primaryBuffer, const HANDLE secondaryBuffer)
    {
        ASSERT(primaryBuffer != nullptr && secondaryBuffer != nullptr, "HANDLE should be not null");

        if (s_instance != nullptr)
        {
            return;
        }

        s_instance = new GameManager(primaryBuffer, secondaryBuffer);
    }

    GameManager::GameManager(const HANDLE primaryBuffer, const HANDLE secondaryBuffer)
        : mPrimaryBuffer(primaryBuffer)
        , mSecondaryBuffer(secondaryBuffer)
        , mBackBuffer(secondaryBuffer)
        , mbSwitched(true)
        , mPlayerObject({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2 })
    {
        for (int y = SCREEN_HEIGHT - 1; y >= 0; --y)
        {
            int x = SCREEN_WIDTH;

            mFrameBuffer[y * (SCREEN_WIDTH + 1) + x] = '\n';
            for (--x; x >= 0; --x)
            {
                mFrameBuffer[y * (SCREEN_WIDTH + 1) + x] = ' ';
            }
        }

        mFrameBuffer[BUFFER_SIZE - 1] = '\0';

        const COORD SIZE = {
            SCREEN_WIDTH << 1,
            SCREEN_HEIGHT << 1
        };

        SetConsoleScreenBufferSize(mPrimaryBuffer, SIZE);
        SetConsoleScreenBufferSize(mSecondaryBuffer, SIZE);

        SMALL_RECT rect = {
            0,
            0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        };

        int retValue = SetConsoleWindowInfo(mPrimaryBuffer, true, &rect);
        ASSERT(retValue != 0, "Failed SetConsoleWindowInfo");

        retValue = SetConsoleWindowInfo(mSecondaryBuffer, true, &rect);
        ASSERT(retValue != 0, "Failed SetConsoleWindowInfo");

        srand(time(nullptr));

        for (int i = ENEMY_COUNT; i > 0; --i)
        {
            mEnemyQueue.push(new Enemy({ 0, 0 }));
        }

        mEnemies.reserve(ENEMY_COUNT);
    }

    GameManager::~GameManager()
    {
        /*while (!mPlayerAmmos.empty())
        {
            delete mPlayerAmmos.front();
            mPlayerAmmos.pop();
        }*/
    }

    GameManager* GameManager::GetInstance()
    {
        ASSERT(s_instance != nullptr, "Should call CreateInstance before calling this function");

        return s_instance;
    }

    /*void GameManager::DeleteInstance()
    {
        delete s_instance;
    }*/

    bool GameManager::Run()
    {
        if (mPlayerObject.mHp == 0)
        {
            memset(mFrameBuffer, 0, BUFFER_SIZE * sizeof(wchar_t));
            _swprintf(mFrameBuffer, TEXT("\n\n\n\n\nGAME OVER!\n\n\n\n\n"));

            SetConsoleActiveScreenBuffer(mBackBuffer);
            system("cls");

            WriteConsole(mBackBuffer, mFrameBuffer, BUFFER_SIZE, nullptr, nullptr);

            system("pause");

            return false;
        }

        if (mEnemies.size() < ENEMY_COUNT)
        {
            Enemy* newEnemy = mEnemyQueue.front();
            mEnemyQueue.pop();

            newEnemy->mLocalOrigin = { rand() % SCREEN_WIDTH, rand() % (SCREEN_HEIGHT / 2) };
            newEnemy->mIsAlive = true;
            newEnemy->Reload();

            mEnemies.push_back(newEnemy);
        }

        overwriteObject(L' ', L' ');

        // Player action
        {
            mPlayerObject.Move();
            Ammo* newAmmo = mPlayerObject.AttackOrNull();

            if (newAmmo != nullptr)
            {
                mPlayerAmmos.push(newAmmo);
            }

            for (int i = mPlayerAmmos.size(); i > 0; --i)
            {
                Ammo* ammo = mPlayerAmmos.front();
                mPlayerAmmos.pop();

                mFrameBuffer[GetFrameIndex(ammo->mLocalOrigin.x, ammo->mLocalOrigin.y)] = ' ';

                ammo->Move();

                if (ammo->mLocalOrigin.y < 0)
                {
                    mPlayerObject.RetrieveAmmo(ammo);
                }
                else
                {
                    mPlayerAmmos.push(ammo);
                }

                mFrameBuffer[GetFrameIndex(ammo->mLocalOrigin.x, ammo->mLocalOrigin.y)] = '*';
            }
        }

        // Enemy action
        {
            for (Enemy* e : mEnemies)
            {
                Ammo* ammo = e->AttackOrNull();

                if (ammo != nullptr)
                {
                    mFrameBuffer[GetFrameIndex(ammo->mLocalOrigin.x, ammo->mLocalOrigin.y)] = ' ';

                    ammo->Move();

                    if (ammo->mLocalOrigin.y < SCREEN_HEIGHT)
                    {
                        mFrameBuffer[GetFrameIndex(ammo->mLocalOrigin.x, ammo->mLocalOrigin.y)] = '@';
                    }
                    else
                    {
                        e->Reload();
                    }
                }
            }
        }

        // CollisionCheck
        {
            const Vector2D_t playerPos = mPlayerObject.mLocalOrigin;

            for (Enemy* e : mEnemies)
            {
                const Vector2D_t ammoPos = e->mAmmo->mLocalOrigin;

                if (playerPos.x == ammoPos.x && playerPos.y == ammoPos.y)
                {
                    mPlayerObject.OnCollision();

                    continue;
                }

                for (const Vector2D_t v : mPlayerObject.mVectors)
                {
                    if (playerPos.x + v.x == ammoPos.x && playerPos.y + v.y == ammoPos.y)
                    {
                        mPlayerObject.OnCollision();

                        break;
                    }
                }
            }

            for (int i = mPlayerAmmos.size(); i > 0; --i)
            {
                Ammo* ammo = mPlayerAmmos.front();

                Vector2D_t ammoPos = ammo->mLocalOrigin;

                mPlayerAmmos.pop();
                {
                    for (std::vector<Enemy*>::iterator iter = mEnemies.begin(); iter != mEnemies.end();)
                    {
                        Vector2D_t enemyPos = (*iter)->mLocalOrigin;

                        if (enemyPos.x == ammoPos.x && enemyPos.y == ammoPos.y)
                        {
                            (*iter)->OnCollision();

                            mFrameBuffer[GetFrameIndex((*iter)->mAmmo->mLocalOrigin.x, (*iter)->mAmmo->mLocalOrigin.y)] = L' ';

                            mEnemyQueue.push(*iter);
                            iter = mEnemies.erase(iter);

                            continue;
                        }

                        for (Vector2D_t v : (*iter)->mVectors)
                        {
                            if (enemyPos.x + v.x == ammoPos.x && enemyPos.y + v.y == ammoPos.y)
                            {
                                (*iter)->OnCollision();

                                mFrameBuffer[GetFrameIndex((*iter)->mAmmo->mLocalOrigin.x, (*iter)->mAmmo->mLocalOrigin.y)] = L' ';

                                mEnemyQueue.push(*iter);
                                iter = mEnemies.erase(iter);

                                goto next;
                            }
                        }

                        ++iter;

                    next:;
                    }
                }

                mPlayerAmmos.push(ammo);
            }
        }

        overwriteObject(L'x', 'O');

        int retValue = WriteConsole(mBackBuffer, mFrameBuffer, BUFFER_SIZE, nullptr, nullptr);
        ASSERT(retValue != 0, "Failed WriteConsole");

        SetConsoleActiveScreenBuffer(mBackBuffer);

        if (mbSwitched)
        {
            mBackBuffer = mPrimaryBuffer;
        }
        else
        {
            mBackBuffer = mSecondaryBuffer;
        }

        mbSwitched = !mbSwitched;

        Sleep(1000 / FPS);

        return true;
    }

    void GameManager::RegisterAmmo(Ammo* ammo)
    {
        mPlayerAmmos.push(ammo);
    }

    int GameManager::GetFrameIndex(const int x, const int y)
    {
        return y * (SCREEN_WIDTH + 1) + x;
    }

    void GameManager::overwriteObject(const wchar_t playerPixel, const wchar_t enemyPixel)
    {
        mFrameBuffer[GetFrameIndex(mPlayerObject.mLocalOrigin.x, mPlayerObject.mLocalOrigin.y)] = playerPixel;

        for (int i = VECTOR_COUNT_PLAYER - 1; i >= 0; --i)
        {
            int x = mPlayerObject.mLocalOrigin.x + mPlayerObject.mVectors[i].x;
            int y = mPlayerObject.mLocalOrigin.y + mPlayerObject.mVectors[i].y;

            if (isClipPixel(x, y))
            {
                continue;
            }

            mFrameBuffer[GetFrameIndex(x, y)] = playerPixel;
        }

        for (Enemy* e : mEnemies)
        {
            mFrameBuffer[GetFrameIndex(e->mLocalOrigin.x, e->mLocalOrigin.y)] = enemyPixel;

            for (int i = VECTOR_COUNT_ENEMY - 1; i >= 0; --i)
            {
                int x = e->mLocalOrigin.x + e->mVectors[i].x;
                int y = e->mLocalOrigin.y + e->mVectors[i].y;

                if (isClipPixel(x, y))
                {
                    continue;
                }

                mFrameBuffer[GetFrameIndex(x, y)] = enemyPixel;
            }
        }
    }
}
