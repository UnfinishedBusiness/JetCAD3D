var tools = {};
tools.search_box = function(text){
    var search_dialog = dialog.new({x: 30, y: 30}, {width: 208, height: 60}, "Search");
    dialog.add_input(search_dialog, {x: 3, y: 3}, {width: 200, height: 30}, "search", "", 6);
    dialog.set_element_focus(search_dialog, "search", true);
}
