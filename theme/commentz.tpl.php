<?php

/**
 * @file
 * Default theme implementation for comments.
 */
?>
 <div class="commentz-inner-<?php print $comment['comment_id']; ?> clearfix commentz-box">
  <div class="commentz-body">
    <div class='commentz-header'>
      <div class='commentz-header-avatar'><?php print $comment['avatar']; ?></div>
      <div class='commentz-header-info'>
        <div class='commentz-header-username'><?php print $comment['author']; ?></div>
        <div class='commentz-header-created'><?php print $comment['created']; ?> </div>
      </div>
      <div class='clearfix'></div>
    </div>
    <div>
      <?php print $comment['content'];?>
    </div>
    <div class="commentz-data">
      <span><?php print render($comment['links']) ?></span>
    </div>
    <div>
      <?php print render($comment['responses']); ?>
    </div>
  </div>
</div>