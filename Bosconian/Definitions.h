#ifndef DEFINITIONS
#define DEFINITIONS

#include <structs.h>

#define WIN_POS_X	50
#define WIN_POS_Y	100
#define WIN_WIDTH	900
#define WIN_HEIGHT	600

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
