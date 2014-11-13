<?php

/**
 * @file
 * Default theme implementation for comments.
 */
?>
<div class="comment-inner-<?php print $comment->cid; ?> clearfix"
<?php  print $attributes; ?>>
  <div class="comment-body">
  <?php  if(variable_get('better_comments_picture') == 1): ?>
    <?php print $picture; ?>
<?php endif;?>
  <?php print render($title_preffix); ?>

  <div class="comment-content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
    hide($content['links']);
    // Print username.
    print $author;
    print render($content);?>

     <div class="comment-data">
   <span><?php print $created; ?></span>
   <span><?php print render($content['links']) ?></span>

    <?php if ($signature): ?>
    <div class="user-signature clearfix">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>
   </div>
  </div>
</div>
