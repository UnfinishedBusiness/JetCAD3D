include("scripts/console.js");
include("scripts/draw.js");
include("scripts/geometry.js");
include("scripts/dialog.js");

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
function test_arcs()
{
    scale = 1;
    for (var x = 0; x < 100; x++)
    {
        draw.polar_line({x: 0, y: 0}, 2 * scale, 90, true);
        draw.polar_line({x: 0, y: 0}, 2 * scale, 0, true);
        draw.arc({x: 0, y:0 }, 0, 90, 2 * scale, true);
        scale ++;
    }
}
function test()
{
    var test = dialog.new({x: 100, y: 100}, {width: 300, height: 300}, "Test");
    dialog.add_button(test, {x: 10, y: 10}, {width: 50, height: 30}, "OK", function(){
        print("You clicked OK on test\n");
    });
    dialog.add_button(test, {x: 80, y: 10}, {width: 70, height: 30}, "Cancel", function(){
        print("You Cancel on test\n");
    });

    var test1 = dialog.new({x: 300, y: 100}, {width: 300, height: 300}, "Test1");
    dialog.add_button(test1, {x: 10, y: 10}, {width: 50, height: 30}, "OK", function(){
        print("You clicked OK on test1\n");
    });
    dialog.add_button(test1, {x: 80, y: 10}, {width: 70, height: 30}, "Cancel", function(){
        print("You Cancel on test1\n");
        dialog.close(test1);
    });
    dialog.add_label(test1, {x: 10, y: 100}, "Pierce Height: ");
    dialog.add_input(test1, {x: 130, y: 90}, {width: 100, height: 30}, "0.1875");
}