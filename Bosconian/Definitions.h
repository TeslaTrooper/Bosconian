#ifndef DEFINITIONS
#define DEFINITIONS

#include <structs.h>

#define WIN_POS_X	50
#define WIN_POS_Y	100
#define WIN_WIDTH	900
#define WIN_HEIGHT	600

#define DIRECTION_LEFT			0
#define DIRECTION_UP			1
#define DIRECTION_RIGHT			2
#define DIRECTION_DOWN			3
#define DIRECTION_LEFT_UP		4
#define DIRECTION_LEFT_DOWN		5
#define DIRECTION_RIGHT_UP		6
#define DIRECTION_RIGHT_DOWN	7

#define CLASS_ID_GAME_OBJECT	0
#define CLASS_ID_SHIP			1

#define IN_GAME_RASTER_SIZE Vec2(50, 50)

namespace Rendering {

	struct Rectangle {
		Vec2 position;
		Vec2 size;

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
		static const Rendering::Rectangle SPRITE_UP			= { Vec2(0, 0), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_DOWN		= { Vec2(0, 1), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT		= { Vec2(0, 2), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT		= { Vec2(0, 3), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT_UP	= { Vec2(0, 4), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT_DOWN	= { Vec2(0, 5), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT_UP	= { Vec2(0, 6), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT_DOWN = { Vec2(0, 7), Vec2(1, 1) };
	}

	namespace Enemy1 {
		static const Rendering::Rectangle SPRITE_UP		= { Vec2(1, 0), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_DOWN	= { Vec2(1, 1), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT	= { Vec2(1, 2), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT	= { Vec2(1, 3), Vec2(1, 1) };
	}

	namespace Enemy2 {
		static const Rendering::Rectangle SPRITE_UP		= { Vec2(2, 0), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_DOWN	= { Vec2(2, 1), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT	= { Vec2(2, 2), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT	= { Vec2(2, 3), Vec2(1, 1) };
	}

	namespace Spy {
		static const Rendering::Rectangle SPRITE_UP		= { Vec2(3, 0), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_DOWN	= { Vec2(3, 1), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_LEFT	= { Vec2(3, 2), Vec2(1, 1) };
		static const Rendering::Rectangle SPRITE_RIGHT  = { Vec2(3, 3), Vec2(1, 1) };
	}

	namespace Obstacle {
		static const Rendering::Rectangle ASTEROID = { Vec2(4, 0), Vec2(1, 1) };
		static const Rendering::Rectangle MINE = { Vec2(4, 1), Vec2(1, 1) };
	}

	namespace Station {
		static const Rendering::Rectangle NODE			= { Vec2(4, 2), Vec2(1, 1) };
		static const Rendering::Rectangle NODE_DAMAGEd	= { Vec2(4, 3), Vec2(1, 1) };
		static const Rendering::Rectangle CORE			= { Vec2(4, 7), Vec2(2, 1) };
		static const Rendering::Rectangle CONNECTORS	= { Vec2(4, 4), Vec2(2, 3) };
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

#endif DEFINITIONS
