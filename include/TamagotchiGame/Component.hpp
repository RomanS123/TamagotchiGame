
/*ll the UI components derive from this class to
 provide unified interface to work with
*/
class Component {
	uint32_t relative_x;
	uint32_t relative_y;
	uint32_t width;
	uint32_t height;
	public:

	uint32_t GetX() const {
		return relative_x;
	}

	uint32_t GetY() const {
		return relative_y;
	}

	uint32_t GetWidth() const {
		return width;
	}

	uint32_t GetHeight() const {
		return height;
	}

	virtual void render(void* callee) = 0;
};
