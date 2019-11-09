var geo = {};

geo.rotatePoint = function(p, o, a)
{
    var rad = a * (3.14159265359 / 180.0);
    var x = Math.cos(rad) * (p.x - o.x) - Math.sin(rad) * (p.y - o.y) + o.x;
    var y = Math.sin(rad) * (p.x - o.x) + Math.cos(rad) * (p.y - o.y) + o.y;
    return { x: parseFloat(x).toFixed(4), y: parseFloat(y).toFixed(4) };
}