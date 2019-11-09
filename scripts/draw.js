var draw = {};

draw.line = function(p0, p1, construction)
{
    add_line(Number(p0.x), Number(p0.y), Number(p1.x), Number(p1.y), construction);
}
draw.polar_line = function(p0, dist, angle, construction)
{
    var p1 = {x: dist, y: 0};
    p1 = geo.rotatePoint(p1, p0, angle);
    this.line(p0, p1, construction);
}
draw.circle = function(center, radius, construction)
{
    add_circle(Number(center.x), Number(center.y), Number(radius), construction);
}
draw.arc = function(center, start_angle, end_angle, radius, construction)
{
    start_angle = start_angle * (3.14159265359 / 180.0);
    end_angle = end_angle * (3.14159265359 / 180.0);
    add_arc(Number(center.x), Number(center.y), Number(start_angle), Number(end_angle), Number(radius), construction);
}