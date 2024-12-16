#include "raylib.h"

#include <chrono>
#include <string>

void clampPaddlePosition(float& y, float height, float bottom)
{
	if(y < 0)
		y = 0.0f;
	else if((y+height) > bottom)
		y = bottom-height;
}
void reflectByRightPaddle(Vector2& ball, float& ballSpeedX, const Vector2& paddle)
{
	if(ball.x >= (paddle.x-20.0f))
	{
		if((ball.y >= paddle.y) && ((ball.y + 20.0f) <= (paddle.y + 50.0f)))
		{
			ball.x = paddle.x-20.0f;
			ballSpeedX = -ballSpeedX;
		}
	}
}
void reflectByLeftPaddle(Vector2& ball, float& ballSpeedX, const Vector2& paddle)
{
	if(ball.x <= (paddle.x+10.0f))
	{
		if((ball.y >= paddle.y) && ((ball.y + 20.0f) <= (paddle.y + 50.0f)))
		{
			ball.x = paddle.x+10.0f; 
			ballSpeedX = -ballSpeedX;
		}
	}
}
void reflectVertical(float y, float height, float& ballSpeedY, float bottom)
{
	if (y < 0 || (y + height) > bottom)
	{
		ballSpeedY = -ballSpeedY;
	}
}

int main(void)
{
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;
	Vector2 ball{100.0f, 200.0f};
	Vector2 player1{20.0f, 200.0f};
	Vector2 player2{370.0f, 200.0f};
	Vector2 ballSpeed{0.05f, 0.05f};
	float dt= 0.0f;

	InitWindow(400, 400, "PONG");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		float p1Speed = 0.0f;
		float p2Speed = 0.0f;
		if (IsKeyDown(KEY_W))
		{
			p1Speed = -0.1f;
		}
		else if (IsKeyDown(KEY_S))
		{
			p1Speed = 0.1f;
		}
		if (IsKeyDown(KEY_UP))
		{
			p2Speed = -0.1f;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			p2Speed = 0.1f;
		}

		ball.x += ballSpeed.x * dt;
		ball.y += ballSpeed.y * dt;
		player1.y += p1Speed * dt;
		player2.y += p2Speed * dt;

		if (ball.x < 0.0f)
		{
			scorePlayer2++;
			ball.x = 100.0f;
			ball.y = 200.0f;
		}
		if ((ball.x + 20.0f) > 400.0f)
		{
			scorePlayer1++;
			ball.x = 100.0f;
			ball.y = 200.0f;
		}
		reflectVertical(ball.y, 20.0f, ballSpeed.y, 400.0f);
		clampPaddlePosition(player1.y, 50.0f, 400.0f);
		clampPaddlePosition(player2.y, 50.0f, 400.0f);
		reflectByLeftPaddle(ball, ballSpeed.x, player1);
		reflectByRightPaddle(ball, ballSpeed.x, player2);

		BeginDrawing();

			ClearBackground(BLACK);
			DrawText(std::to_string(scorePlayer1).c_str(), 100, 0, 30, WHITE);
			DrawText(std::to_string(scorePlayer2).c_str(), 290, 0, 30, WHITE);
			DrawRectangle(200, 0, 1, 400, WHITE);
			DrawRectangleV(ball, {20.f, 20.f}, WHITE);
			DrawRectangleV(player1, {10.f, 50.f}, WHITE);
			DrawRectangleV(player2, {10.f, 50.f}, WHITE);

		EndDrawing();

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}

	CloseWindow();

	return 0;
}