// Movement directions
enum direction { FORWARD, BACKWARDS, RIGHT, LEFT };

// This boolean uses when program starts or unpauses to prevent weird mouse movements. 
// Initially set by true.
bool firstMouseInput = true;

// Stores information about which sides camera must move each updateCameraPosition call.
// Indices are { FORWARD, BACKWARDS, RIGHT, LEFT }.
bool cameraMovement[4];