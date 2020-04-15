var MouseInteraction = {};

MouseInteraction.MouseOverPadding = 0.125;

MouseInteraction.init = function()
{
	//nothing to setup
}
MouseInteraction.tick = function()
{
    var mouse_pos = render.get_mouse();
    for (var x = 0; x < render.stack_size(); x++)
    {
        var entity = render.get_entity(x);
        var touching = false;
        if (entity.type == "line")
        {
            var angle = geometry.measure_polar_angle(entity.start, entity.end) + 90;
            if (angle >= 360) angle -= 360;
            if (angle == 360) angle = 0;
            var line1 = geometry.create_polar_line(mouse_pos, angle, MouseInteraction.MouseOverPadding / 2);
            var angle2 = angle + 180;
            if (angle2 >= 360) angle2 -= 360;
            if (angle2 == 360) angle2 = 0;
            var line2 = geometry.create_polar_line(mouse_pos, angle2, MouseInteraction.MouseOverPadding / 2);
            var actual_line =  { type: 'line', start: line1.end, end: line2.end };
            //console.log(JSON.stringify(actual_line) + "\n");
            //render.add_entity(actual_line);
            var int = geometry.lines_intersect(actual_line, entity);
            //console.log(JSON.stringify(int) + "\n");
            if (int)
            {
                //console.log("Mouse is touching entity #" + x + "\n");
                render.set_entity(x, { color: {r: 0, g: 0, b: 1}});
            }
            else
            {
                render.set_entity(x, { color: {r: 1, g: 1, b: 1}});
            }
        }
    }
}
