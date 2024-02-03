#include "raylib.h"
#define worldSize 512
#define blockSize 10
struct Building {
	int x;
	int y;
	bool alive;
};
struct Game {
	struct Building _buildings[worldSize][worldSize];
};
int updateBuilding(struct Building* _building, struct Game* _game) {
	if (_building->alive) {
		DrawRectangle(_building->x, _building->y, blockSize, blockSize, BLACK);
	}
	//if (CheckCollisionRecs((Rectangle) { GetMouseX(), GetMouseY(), 50, 50 }, (Rectangle) { _building->x, _building->y, blockSize, blockSize})) {
	//	_building->alive = true;
	//}
}
int generation(struct Building* _building, struct Game* _game) {
	int neighbour_count = 0;
	for (int x = -1; x < 2; x += 2) {
		for (int y = -1; y < 2; y += 2) {
			if (_game->_buildings[(int)((_building->y/ blockSize) + y)][(int)((_building->x/ blockSize) + x)].alive) {
				neighbour_count++;
			}
		}
	}
	if (neighbour_count < 2) {
		_building->alive = false;
	}
	if ((neighbour_count == 2 || neighbour_count == 3) && _building->alive) {
		_building->alive = true;
	}
	if (neighbour_count == 3) {
		_building->alive = true;
	}
	if (neighbour_count > 3) {
		_building->alive = false;
	}

	return 0;
}

int genWorld(struct Game* _game) {

	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			if (GetRandomValue(0, 1) == 1) _game->_buildings[y][x].alive = true;
			else _game->_buildings[y][x].alive = false;
			_game->_buildings[y][x].x = x * blockSize;
			_game->_buildings[y][x].y = y * blockSize;

		}
	}
	for (int i = 0; i < 20; i++) {
		for (int x = 0; x < worldSize; x++) {
			for (int y = 0; y < worldSize; y++) {
				generation(&_game->_buildings[y][x], _game);
			
			}
		}
	}
	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			_game->_buildings[y][x].alive = !_game->_buildings[y][x].alive;
		}
	}
	return 0;
}
int runGame(struct Game* _game) {
	SetTargetFPS(60);
	InitWindow(800, 800, "ea");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SKYBLUE);
		for (int x = 0; x < worldSize; x++) {
			for (int y = 0; y < worldSize; y++) {
				updateBuilding(&_game->_buildings[y][x],_game);
			}
		}
		if (IsKeyPressed(KEY_R)) {
			SetRandomSeed(GetRandomValue(0, 1000));
			genWorld(_game);
		}
		EndDrawing();
	}
}
struct Game _game;
int main() {
	runGame(&_game);
	return 0;
}
