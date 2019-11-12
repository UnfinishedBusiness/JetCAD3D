var dialog = {};

dialog.callbacks = [];
dialog.new = function(pos, size, title){
    return new_dialog(pos.x, pos.y, size.width, size.height, title);
}
dialog.close = function(id){
    dialog_close(id);
}
dialog.add_button = function(id, pos, size, label, callback)
{
    dialog_add_button(id, pos.x, pos.y, size.width, size.height, label);
    var cb = {};
    cb.dialog_id = id;
    cb.button_label = label;
    cb.callback = callback;
    dialog.callbacks.push(cb);
}
dialog.add_label = function(id, pos, label)
{
    dialog_add_label(id, pos.x, pos.y, label);
}
dialog.add_input = function (id, pos, size, value)
{
    dialog_add_input(id, pos.x, pos.y, size.width, size.height, value);
}
dialog.element_clicked = function(id)
{
    var args = JSON.parse(id);
    if (args.type == "button_click")
    {
        //print("Clicked button " + args.button_label + " on dialog #" + args.dialog_id + "\n");
        for (var x = 0; x < dialog.callbacks.length; x++)
        {
            if (dialog.callbacks[x].dialog_id == args.dialog_id && dialog.callbacks[x].button_label == args.button_label)
            {
                dialog.callbacks[x].callback();
                return;
            }
        }
    }
}