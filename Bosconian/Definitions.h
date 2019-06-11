#ifndef DEFINITIONS
#define DEFINITIONS

#include <structs.h>
#include <map>

// Generall definitions
#define WIN_POS_X	50
#define WIN_POS_Y	100
#define WIN_WIDTH	900
#define WIN_HEIGHT	600

#define ALPHA_COLOR new Color(141, 0, 200)

// In-Game specific definitions
#define WORLD_WIDTH		1000
#define WORLD_HEIGHT	1500

#define DIRECTION_LEFT			0
#define DIRECTION_UP			1
#define DIRECTION_RIGHT			2
#define DIRECTION_DOWN			3
#define DIRECTION_LEFT_UP		4
#define DIRECTION_LEFT_DOWN		5
#define DIRECTION_RIGHT_UP		6
#define DIRECTION_RIGHT_DOWN	7

#define VECTOR_LEFT			Vec2(-1, 0)
#define VECTOR_UP			Vec2(0, 1)
#define VECTOR_RIGHT		Vec2(1, 0)
#define VECTOR_DOWN			Vec2(0, -1)
#define VECTOR_LEFT_UP		Vec2(-1, 1).norm()
#define VECTOR_LEFT_DOWN	Vec2(-1, -1).norm()
#define VECTOR_RIGHT_UP		Vec2(1, 1).norm()
#define VECTOR_RIGHT_DOWN	Vec2(1, -1).norm()

#define QUADRANT_RIGHT_TOP		1
#define QUADRANT_LEFT_TOP		2
#define QUADRANT_LEFT_BOTTOM	3
#define QUADRANT_RIGHT_BOTTOM	4

#define ENEMY_TYPE_1	1
#define ENEMY_TYPE_2	2
#define ENEMY_TYPE_SPY	3

#define CLASS_ID_GAME_OBJECT		0
#define CLASS_ID_SHIP				1
#define CLASS_ID_SHIP_PROJECTILE	2
#define CLASS_ID_ENEMY				3
#define CLASS_ID_CANNON				4
#define CLASS_ID_STATION_PROJECTILE 5
#define CLASS_ID_STATION_CONNECTOR	6
#define CLASS_ID_STATION_CORE		7
#define CLASS_ID_OBSTACLE			8

#define IN_GAME_RASTER_SIZE Vec2(50, 50)

#define SHIP_SPEED				100
#define SHIP_BULLET_SPEED		500
#define SHIP_SHOOTING_INTERVAL	.2f
#define SHIP_BULLET_LIFETIME	.75f
#define STATION_BULLET_LIFETIME 3
#define ENEMY_SPEED				SHIP_SPEED / 2

namespace Direction {

	const map<int, Vec2> mapping = {
		{ DIRECTION_LEFT, VECTOR_LEFT },
		{ DIRECTION_UP, VECTOR_UP },
		{ DIRECTION_RIGHT, VECTOR_RIGHT },
		{ DIRECTION_DOWN, VECTOR_DOWN },
		{ DIRECTION_LEFT_UP, VECTOR_LEFT_UP },
		{ DIRECTION_LEFT_DOWN, VECTOR_LEFT_DOWN },
		{ DIRECTION_RIGHT_UP, VECTOR_RIGHT_UP },
		{ DIRECTION_RIGHT_DOWN, VECTOR_RIGHT_DOWN }
	};

}

namespace Rendering {

	struct Rectangle {
		Vec2 position;
		Vec2 size;

		Rectangle() : Rectangle(0, 0, 0, 0) {}
		Rectangle(float x, float y, float w, float h) : position(Vec2(x, y)), size(Vec2(w, h)) {}

		bool intersects(const Rectangle& rect) const {
			float r1x = position.x;
			float r1y = position.y;
			float r1w = size.x;
			float r1h = size.y;

			float r2x = rect.position.x;
			float r2y = rect.position.y;
			float r2w = rect.size.x;
			float r2h = rect.size.y;

			return r1x < r2x + r2w &&
				r1x + r1w > r2x &&
				r1y < r2y + r2h &&
				r1h + r1y > r2y;
		}

		bool operator==(const Rectangle& rect) {
			return position == rect.position && size == rect.size;
		}
	};

	struct RenderUnit {
		Mat4 transformation;
		Rectangle textureTransform;
	};

}

namespace TextureAtlas {

	namespace Ship {
		static const Rendering::Rectangle SPRITE_UP			= { 0, 0, 1, 1 };
		static const Rendering::Rectangle SPRITE_DOWN		= { 0, 1, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT		= { 0, 2, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT		= { 0, 3, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_UP	= { 0, 4, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_DOWN	= { 0, 5, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_UP	= { 0, 6, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_DOWN = { 0, 7, 1, 1 };

		const map<int, Rendering::Rectangle> spriteMap = {
			{ DIRECTION_LEFT, SPRITE_LEFT },
			{ DIRECTION_UP, SPRITE_UP },
			{ DIRECTION_RIGHT, SPRITE_RIGHT },
			{ DIRECTION_DOWN, SPRITE_DOWN },
			{ DIRECTION_LEFT_UP, SPRITE_LEFT_UP },
			{ DIRECTION_LEFT_DOWN, SPRITE_LEFT_DOWN },
			{ DIRECTION_RIGHT_UP, SPRITE_RIGHT_UP },
			{ DIRECTION_RIGHT_DOWN, SPRITE_RIGHT_DOWN }
		};
	}

	namespace Enemy1 {
		static const Rendering::Rectangle SPRITE_UP			= { 1, 0, 1, 1 };
		static const Rendering::Rectangle SPRITE_DOWN		= { 1, 1, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT		= { 1, 2, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT		= { 1, 3, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_UP	= { 1, 4, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_DOWN	= { 1, 5, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_UP	= { 1, 6, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_DOWN = { 1, 7, 1, 1 };

		const map<int, vector<Rendering::Rectangle>> spriteMap = {
			{ QUADRANT_RIGHT_TOP,		{ SPRITE_UP, SPRITE_RIGHT_UP, SPRITE_RIGHT } },
			{ QUADRANT_LEFT_TOP,		{ SPRITE_UP, SPRITE_LEFT_UP, SPRITE_LEFT } },
			{ QUADRANT_LEFT_BOTTOM,		{ SPRITE_LEFT, SPRITE_LEFT_DOWN, SPRITE_DOWN } },
			{ QUADRANT_RIGHT_BOTTOM,	{ SPRITE_RIGHT, SPRITE_RIGHT_DOWN, SPRITE_DOWN } }
		};
	}

	namespace Enemy2 {
		static const Rendering::Rectangle SPRITE_UP			= { 2, 0, 1, 1 };
		static const Rendering::Rectangle SPRITE_DOWN		= { 2, 1, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT		= { 2, 2, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT		= { 2, 3, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_UP	= { 2, 4, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_DOWN	= { 2, 5, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_UP	= { 2, 6, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_DOWN = { 2, 7, 1, 1 };

		const map<int, vector<Rendering::Rectangle>> spriteMap = {
			{ QUADRANT_RIGHT_TOP,		{ SPRITE_UP, SPRITE_RIGHT_UP, SPRITE_RIGHT } },
			{ QUADRANT_LEFT_TOP,		{ SPRITE_UP, SPRITE_LEFT_UP, SPRITE_LEFT } },
			{ QUADRANT_LEFT_BOTTOM,		{ SPRITE_LEFT, SPRITE_LEFT_DOWN, SPRITE_DOWN } },
			{ QUADRANT_RIGHT_BOTTOM,	{ SPRITE_RIGHT, SPRITE_RIGHT_DOWN, SPRITE_DOWN } }
		};
	}

	namespace Spy {
		static const Rendering::Rectangle SPRITE_UP			= { 3, 0, 1, 1 };
		static const Rendering::Rectangle SPRITE_DOWN		= { 3, 1, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT		= { 3, 2, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT		= { 3, 3, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_UP	= { 3, 4, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_DOWN	= { 3, 5, 1, 1 };
		static const Rendering::Rectangle SPRITE_LEFT_UP	= { 3, 6, 1, 1 };
		static const Rendering::Rectangle SPRITE_RIGHT_DOWN = { 3, 7, 1, 1 };

		const map<int, vector<Rendering::Rectangle>> spriteMap = {
			{ QUADRANT_RIGHT_TOP,		{ SPRITE_UP, SPRITE_RIGHT_UP, SPRITE_RIGHT } },
			{ QUADRANT_LEFT_TOP,		{ SPRITE_UP, SPRITE_LEFT_UP, SPRITE_LEFT } },
			{ QUADRANT_LEFT_BOTTOM,		{ SPRITE_LEFT, SPRITE_LEFT_DOWN, SPRITE_DOWN } },
			{ QUADRANT_RIGHT_BOTTOM,	{ SPRITE_RIGHT, SPRITE_RIGHT_DOWN, SPRITE_DOWN } }
		};
	}

	namespace Obstacle {
		static const Rendering::Rectangle ASTEROID	= { 4, 0, 1, 1 };
		static const Rendering::Rectangle MINE		= { 4, 1, 1, 1 };
	}

	namespace Station {
		static const Rendering::Rectangle NODE			= { 4, 2, 1, 1 };
		static const Rendering::Rectangle NODE_DAMAGED	= { 4, 3, 1, 1 };
		static const Rendering::Rectangle CORE			= { 4, 7, 2, 1 };
		static const Rendering::Rectangle CONNECTORS	= { 4, 4, 2, 3 };
	}

	namespace Font {
		static const Rendering::Rectangle ZERO		= { 3, 1, 1, 1 };
		static const Rendering::Rectangle ONE		= { 0, 0, 1, 1 };
		static const Rendering::Rectangle TWO		= { 1, 0, 1, 1 };
		static const Rendering::Rectangle THREE		= { 2, 0, 1, 1 };
		static const Rendering::Rectangle FOUR		= { 3, 0, 1, 1 };
		static const Rendering::Rectangle FIVE		= { 4, 0, 1, 1 };
		static const Rendering::Rectangle SIX		= { 5, 0, 1, 1 };
		static const Rendering::Rectangle SEVEN		= { 0, 1, 1, 1 };
		static const Rendering::Rectangle EIGHT		= { 1, 1, 1, 1 };
		static const Rendering::Rectangle NINE		= { 2, 1, 1, 1 };
		static const Rendering::Rectangle SCORE		= { 0, 2, 5, 1 };
		static const Rendering::Rectangle ROUND		= { 0, 3, 5, 1 };

		const map<char, Rendering::Rectangle> numberMap = {
			{'0', ZERO},
			{'1', ONE},
			{'2', TWO},
			{'3', THREE},
			{'4', FOUR},
			{'5', FIVE},
			{'6', SIX},
			{'7', SEVEN},
			{'8', EIGHT},
			{'9', NINE},
		};
	}

	namespace Background {
		static const Rendering::Rectangle RECT = { 0, 0, 4, 4 };
	}

	namespace Explosion {
		static const Rendering::Rectangle EXP_1 = { 5, 3, 1, 1 };
		static const Rendering::Rectangle EXP_2 = { 5, 2, 1, 1 };
		static const Rendering::Rectangle EXP_3 = { 5, 1, 1, 1 };
		static const Rendering::Rectangle EXP_4 = { 5, 0, 1, 1 };
		static const Rendering::Rectangle EXP_5 = { 6, 0, 1, 1 };
		static const Rendering::Rectangle EXP_6 = { 6, 1, 1, 1 };

		static const map<int, Rendering::Rectangle> expMap = {
			{ 0, EXP_1 },
			{ 1, EXP_2 },
			{ 2, EXP_3 },
			{ 3, EXP_4 },
			{ 4, EXP_5 },
			{ 5, EXP_6 },
		};
	}

	namespace Missile {
		static const Rendering::Rectangle ROCKET_UP_WARDS		= { 6, 7, 1, 1 };
		static const Rendering::Rectangle ROCKET_DOWN_WARDS		= { 6, 6, 1, 1 };
		static const Rendering::Rectangle BULLET				= { 6, 2, 1, 1 };
		static const Rendering::Rectangle PLAYER_BULLET			= { 6, 5, 1, 1 };
	}

}

namespace ModelData {

	static const int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	static const float vertices[] = {
		// pos			texture
		1.0f, 1.0f,		1.0f, 1.0f, // top right
		1.0f, 0.0f,		1.0f, 0.0f, // bottom right
		0.0f, 0.0f,		0.0f, 0.0f, // bottom left
		0.0f, 1.0f,		0.0f, 1.0f  // top left
	};

	static const int sizes[] = {
		2, 2
	};

	static Binding::VertexData vertexData = { vertices, 4, 4 };
	static Binding::IndexData indexData = { indices, 6 };
	static Binding::AttributeData attributeData = { sizes, 2 };

	static Binding::Bindable quadBindable = { vertexData, indexData, attributeData };
}

namespace Station {

	static Vec2 getCorePosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(65, 50);
	}
	
	static Vec2 getLeftCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(-25, 50);
	}

	static Vec2 getLeftBottomCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(25, -25);
	}

	static Vec2 getLeftTopCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(25, 125);
	}

	static Vec2 getRightCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(205, 50);
	}

	static Vec2 getRightBottomCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(155, -25);
	}

	static Vec2 getRightTopCannonPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(155, 125);
	}

	static Vec2 getRightConnectorPosition(const Vec2& stationPosition) {
		return stationPosition + Vec2(130, 0);
	}

	struct ProjectileParams {
		const Vec2 position;
		const Vec2 direction;
		const float speed;

		ProjectileParams(const Vec2& position, const Vec2& direction, float speed) : position(position), direction(direction), speed(speed) {}
	};

}

#endif DEFINITIONS
