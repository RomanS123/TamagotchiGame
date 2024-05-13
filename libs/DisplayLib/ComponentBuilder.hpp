template <typename T>
class ComponentBuilder {
  T* component_ = nullptr;
	bool retrieved_ = true;
 public:
  ComponentBuilder() {
	Reset();
  }

  ComponentBuilder<T>& SetPosition(uint32_t x, uint32_t y) {
    component_->SetPosition(x, y);
    return *this;
  }

  ComponentBuilder<T>& SetSize(uint32_t width, uint32_t height) {
    component_->SetSize(width, height);
    return *this;
  }

  T* Build() {
	  T* ptr = component_;
	  Reset();
	  return ptr; 
  }
	
  void Reset() {
		component_ = new T();
	}

  ~ComponentBuilder() {
	delete component_;
  }
};
