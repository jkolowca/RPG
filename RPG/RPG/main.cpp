#include "Application.h"
int main() {
	Application app;
	while (app.GetWindow()->IsOpen()) {
		app.Update();
		app.Render();
	}
	return 0;
}