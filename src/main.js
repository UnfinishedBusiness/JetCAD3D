include("src/UserInterface.js");
include("src/MouseInteraction.js");
include("src/Tools.js");

function setup()
{
    UserInterface.init();
    Tools.init();
    MouseInteraction.init();
}
function loop()
{
	UserInterface.tick();
    Tools.tick();
    MouseInteraction.tick();
}