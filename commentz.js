(function($) {
  Drupal.behaviors.commentz = {
    attach : function(context, settings) {
      
      $(".commentz-delete-cancel").click(function() {
        var $confirmationForm = $(this).parents('form#commentz-confirm-delete-form').fadeOut('slow');
        // Remove from the dom, as we don't want it anymore.
        setTimeout(function() {
          $confirmationForm.remove();
        }, 2000);
      });
      
      $('.commentz-edit-cancel').click(function() {
        $(this).parents('.commentz-content-wrapper').find('.commentz-content').removeClass('hide').addClass('show');
        $(this).parents('.commentz-body').find('.commentz-links').removeClass('hide').addClass('show');
        $(this).parents('.commentz-form').hide().remove();
      });
      
      // Prevent multiple confirm delete form.
      // @todo use event delegation
      $('li.commentz-delete a').click(function(e) {
        if (!$(this).parents('.commentz-links').find('.commentz-delete-confirm').length) {
          e.preventDefault();
          return false;
        }
      });
      
      // Toggle comment response form
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
}(jQuery));
