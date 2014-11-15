<?php

/**
 * @file
 * Default theme implementation for comments.
 */
?>
<div class="commentz-inner-<?php print $comment->cid; ?> clearfix commentz-box"<?php  print $attributes; ?>>
  <div class="commentz-body">
    <div class='commentz-header'>
      <div class='commentz-header-avatar'><?php print $picture; ?></div>
      <div class='commentz-header-info'>
        <div class='commentz-header-username'><?php print $author; ?></div>
        <div class='commentz-header-created'><?php print $created; ?> </div>
      </div>
      <?php print render($title_preffix); ?>
      <div class='clearfix'></div>
    </div>
    <div class="commentz-content"<?php print $content_attributes; ?>>
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['links']);
        print render($content);
      ?>

      <div class="commentz-data">

        <span><?php print render($content['links']) ?></span>

        <?php if ($signature): ?>
          <div class="user-signature clearfix">
            <?php print $signature ?>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class='commentz-response'>
    <?php print $commentz_response_wrapper;?>
  </div>
</div>
