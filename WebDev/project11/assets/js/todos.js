$("ul").on("click", "li", function(){

    $(this).toggleClass("completed");
});


//click on an X to delete item
$("ul").on("click", "span", function(event){
    $(this).parent().fadeOut(500, function(){
        $(this).remove();
    });
    event.stopPropagation();
});


$("input[type=text]").keypress(function(event){
    if(event.which === 13)

    {
        //Grab the user input
        var todoText = $(this).val();
        //Reset field to be empty
        $(this).val("");
        //Create a new li and add to ul
        $("ul").append("<li><span><i class='fas fa-trash'></i></span> " + todoText + "</li>")
    }

});
