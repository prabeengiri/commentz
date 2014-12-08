(function($) {
  Drupal.behaviors.commentz = {
    attach : function(context, settings) {
      
      $(".commentz-delete-cancel").click(function() {
        var $confirmationForm = $(this).parents('form#commentz-confirm-delete-form');
        $confirmationForm.parents('.commentz-links').find('ul.links').removeClass('hide').addClass('show');
        $confirmationForm.remove();
        
      });
      
      $('.commentz-edit-cancel').click(function() {
        $(this).parents('.commentz-content-wrapper').find('.commentz-content').removeClass('hide').addClass('show');
        $(this).parents('.commentz-body').find('.commentz-links').removeClass('hide').addClass('show');
        $(this).parents('.commentz-form').hide().remove();
      });
      
      // Toggle comment response form.
      $('a.commentz-add-response-link').on('click', function() {
         var $response_form = $(this)
          .parents('.commentz-body')
          .find('.commentz-response-form');
          
          //$response_form.toggleClass('show');
          $response_form.removeClass('hide').addClass('show');
        
        /*$('html, body').animate({
          scrollTop: $response_form.offset().top - 100
        }, 500);
        */
      });
      
      // Show response delete link on hover.
      $('.commentz-response-inner').once().hover(function() {
        $(this).find('.commentz-response-delete-link').toggle();
      });
    }
  };
  
  /**
   * Update the comment counter.
   */
  Drupal.ajax.prototype.commands.updateCommentzCounter =  function(ajax, response, status) {
    alert('yes');
  };
}(jQuery));
