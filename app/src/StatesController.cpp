#include <TamagotchiGame/StatesController.hpp>
#include <functional>

StatesController* StatesController::instance_ = nullptr;

StatesController* StatesController::GetInstance() {
	if(instance_ == nullptr) {
		instance_ = new StatesController();
	}
	return instance_;
}

void StatesController::AddAction(void* object, std::function<void()> action) {
	mapping_[object].push_front(action);
}

//calls actions attached to callee
void StatesController::Update(void* callee) {
	for(auto& callback : mapping_[callee]) {
		callback();
	}
}

void StatesController::Clear() {
	mapping_.clear();
}
