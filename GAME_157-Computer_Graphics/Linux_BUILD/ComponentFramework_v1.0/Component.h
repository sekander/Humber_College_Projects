#pragma once
class Component {
	public:
		Component(Component* parent_)  {
			parent = parent_;
		}
		virtual ~Component() { parent = nullptr; }
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float deltaTime_) = 0;
		virtual void Render()const = 0;
	protected:
		Component* parent;
};


