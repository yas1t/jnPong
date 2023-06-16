#include "include/raylib.h"
#include <stdlib.h>
#include <synchapi.h> //retar

struct ball {
	float x, y;
	float radius;
	float speedx, speedy;
	Color col;

	void draw() {
		DrawCircle((int)x, (int)y, radius, col);
	}
};
struct paddle {
	float x, y;
	float speed;
	float width, height;
	int score;
	Color col;

	Rectangle getRect() {
		Rectangle rec;
		rec.x = x;
		rec.y = y;
		rec.width = width;
		rec.height = height;
		
		return rec;
	}
	Rectangle draw() {
		DrawRectangle(x, y, width, height, col);
	}
};

int main(int argc, char *argv[]) {
	InitWindow(1200, 850, "jnPong");  // jnBaw
	SetTargetFPS(120);

	int scoreL, scoreR;

	paddle padL;
	padL.x = 100;
	padL.y = 400;
	padL.width = 16;
	padL.height = 256;
	padL.col = RED;
	padL.score = 0;

	paddle padR;
	padR.x = 1100;
	padR.y = 400;
	padR.width = 16;
	padR.height = 256;
	padR.col = BLUE;
	padR.score = 0;

	Rectangle leftGoal;
	leftGoal.x = 0;
	leftGoal.y = 0;
	leftGoal.width = 5;
	leftGoal.height = GetScreenHeight();

	Rectangle rightGoal;
	rightGoal.x = GetScreenWidth()-5;
	rightGoal.y = 0;
	rightGoal.width = 5;
	rightGoal.height = GetScreenHeight();

	Rectangle bottom;
	bottom.x = 0;
	bottom.y = GetScreenHeight();
	bottom.width = GetScreenWidth();
	bottom.height = 5;

	Rectangle top;
	top.x = 0;
	top.y = 0;
	top.width = GetScreenWidth();
	top.height = 5;

	ball ball;
	ball.x = (GetScreenWidth() / 2);
	ball.y = (GetScreenHeight() / 2);
	ball.radius = 24.0f;
	ball.speedx = 4;
	ball.speedy = 4;
	ball.col = WHITE;

	int valx = 1;
	int valy = 1;

	char buff[8];
		
	while(!WindowShouldClose()) {
		BeginDrawing();

			ClearBackground(BLACK);
			padL.draw();
			padR.draw();
			ball.draw();

			DrawRectangleRec(leftGoal, BLUE);
			DrawRectangleRec(rightGoal, RED);

			DrawRectangleRec(bottom, BLACK);
			DrawRectangleRec(top, BLACK);

			
			itoa(padL.score, buff, 8);
			DrawText(buff, 20, 20, 40, GREEN);

			itoa(padR.score, buff, 8);
			DrawText(buff, 1180, 20, 40, GREEN);
			
		EndDrawing();

		ball.x += valx * ball.speedx;
		ball.y += valy * ball.speedy;

		IsKeyDown(KEY_W) ? padL.y -= 3 : 0;
		IsKeyDown(KEY_S) ? padL.y += 3 : 0; 
		
		IsKeyDown(KEY_UP)   ? padR.y -= 3 : 0;
		IsKeyDown(KEY_DOWN) ? padR.y += 3 : 0;

		if (CheckCollisionCircleRec((Vector2) {ball.x, ball.y}, ball.radius, padR.getRect())) valx *= -1;
		if (CheckCollisionCircleRec((Vector2) { ball.x, ball.y }, ball.radius, padL.getRect())) valx *= -1;
		if (CheckCollisionCircleRec((Vector2) { ball.x, ball.y }, ball.radius, bottom))	valy *= -1;
		if (CheckCollisionCircleRec((Vector2) { ball.x, ball.y }, ball.radius, top)) valy *= -1;
		
		// goals //
		if (CheckCollisionCircleRec((Vector2) { ball.x, ball.y }, ball.radius, leftGoal)) {
			ball.x = (GetScreenWidth() / 2);
			ball.y = (GetScreenHeight() / 2);
			padR.score += 1;
			Sleep((DWORD)2000);
			valx = 1;
			valy = 1;

		}
		if (CheckCollisionCircleRec((Vector2) { ball.x, ball.y }, ball.radius, rightGoal)) {
			ball.x = (GetScreenWidth()  / 2);
			ball.y = (GetScreenHeight() / 2);
			padL.score += 1;
			Sleep((DWORD)2000);
			valx = -1;
			valy = 1;
		}
	}

	CloseWindow();
}
