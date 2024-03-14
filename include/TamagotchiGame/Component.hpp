
/*
 All the UI components derive from this class to
 provide unified interface to work with
*/
class Component {
	uint32_t relative_x;
	uint32_t relative_y;
	uint32_t width;
	uint32_t height;
	public:

	uint32_t GetX() const;

	uint32_t GetY() const;

	uint32_t GetWidth() const;

	uint32_t GetHeight() const;

	virtual void render(void* callee) = 0;
};
