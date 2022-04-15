#pragma once
class Status
{
public:
	// constrcuter destructer
	Status();
	~Status();

	// delete Function
	Status(const Status& _Other) = delete;
	Status(Status&& _Other) noexcept = delete;
	Status& operator=(const Status& _Other) = delete;
	Status& operator=(Status&& _Other) noexcept = delete;

protected:

private:

};
