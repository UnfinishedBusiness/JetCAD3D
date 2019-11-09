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