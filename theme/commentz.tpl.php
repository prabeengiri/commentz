<?php

/**
 * @file
 * Default theme implementation for comments.
 */
?>
 <div id ="commentz-inner-<?php print $comment['comment_id']; ?>"  class="clearfix commentz-box">
  <div class="commentz-body">
    <div class='commentz-header'>
      <div class='commentz-header-avatar'><?php print $comment['avatar']; ?></div>
      <div class='commentz-header-info'>
        <div class='commentz-header-username'><?php print $comment['author']; ?></div>
        <div class='commentz-header-created'><?php print $comment['created']; ?> </div>
      </div>
      <div class='clearfix'></div>
    </div>
    <div class='commentz-content-wrapper'>
      <div class='commentz-content'> <?php print $comment['content'];?> </div>
    </div>
    <div class="commentz-links">
      <span><?php print render($comment['links']) ?></span>
      <div id="commentz-delete-confirm-<?php print $comment['comment_id'];?>" class='commentz-delete-confirm'></div>
    </div>
    <div class='commentz-response-wrapper'>
      <div id='commentz-responses-<?php print $comment['comment_id']?>'>
        <?php print render($comment['responses']); ?>
      </div>
      <?php print render($commentz['commentz_response_form']); ?>
    </div>

  </div>
</div>