#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

class IconObject;
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();

	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time delta_time) override;

	void onFinishedExecution() override;

private:
	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	typedef std::vector<IconObject*> IconList;

	IconList icon_list;

	const float STREAMING_LOAD_DELAY = 10.0f;
	const StreamingType streaming_type = SINGLE_STREAM;
	float ticks = 0.0f;
	bool started_streaming = false;

	int column_grid = 0; int row_grid = 0;
	int num_displayed = 0;
	//const int MAX_COLUMN = 28;
	const int MAX_COLUMN = 9;
	//const int MAX_ROW = 22;
	const int MAX_ROW = 1;

	void spawnObject();
};