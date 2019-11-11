var dialog = {};

dialog.callbacks = [];
dialog.new = function(pos, size, title){
    return new_dialog(pos.x, pos.y, size.width, size.height, title);
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
dialog.element_clicked = function(id)
{
    var args = JSON.parse(id);
    if (args.type == "button_click")
    {
        print("Clicked button " + args.button_label + " on dialog #" + args.dialog_id + "\n");
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