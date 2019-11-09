include("scripts/console.js");
include("scripts/draw.js");
include("scripts/geometry.js");

function line_test()
{
    console.log("Drawing lines!\n");
    var last_endpoint = null;
    var end_point = { x: 0, y: 10 };
    for (var x = 0; x < 100; x++)
    {
        if (last_endpoint != null) //Skip first Pass
        {
            draw.line(last_endpoint, end_point, false);
        }
        last_endpoint = end_point;
        draw.line({x: 0, y: 0}, end_point, true);
        end_point = geo.rotatePoint(end_point, {x: 0, y: 0}, -1);
    }
    draw.line({ x: 0, y: 10 }, last_endpoint, false);
}
function polar_line_test()
{
    //Draw polar line
    draw.polar_line({x: 0, y: 0}, 2, 110, true);
}
function test_circles()
{
    radius = 1;
    for (var x = 0; x < 100; x++)
    {
        draw.circle({x: 0, y: 0}, radius, false);
        radius += 0.125;
    }   
}