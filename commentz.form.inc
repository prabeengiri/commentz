<?php
/**
 * Form builder; Builds the confirmation form for deleting a single comment.
 *
 * @ingroup forms
 * @see commentz_confirm_delete_submit()
 */
function commentz_confirm_delete_form($form, &$form_state, $commentz) {
  $form['#commentz'] = $commentz;

  $form['actions']['submit'] = array(
    '#prefix' => "<span class='commentz-delete-confirm-prefix'>" . t('Delete comment and its responses?') . " </span>",
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#ajax' => array(
      'callback' => 'commentz_confirm_delete_form_submit',
      'wrapper' => 'comment-wrapper',
      'method' => 'append',
      'effect' => 'fade',
    ),
    '#suffix' => "<a href='javascript:;' class='commentz-delete-cancel'>" . t('Cancel') . "</a>",
  );

  $form['#attributes'] = array('class' => array('well', 'well-sm'));

  // Always provide entity id in the same form key as in the entity edit form.
  $form['cid'] = array('#type' => 'value', '#value' => $commentz->cid);
  return $form;
}

/**
 * Delete the comment by calling comment_delete.
 */
function commentz_confirm_delete_form_submit(&$form, &$form_state) {
  $commentz = $form['#commentz'];
  // Delete the comment and its replies.
  commentz_delete($commentz['cid']);
  // drupal_set_message(t('The comment and all its replies have been.'));
  watchdog('commentz', 'Deleted commentz @cid and its replies.', array('@cid' => $commentz['cid']));
  // Clear the cache so an anonymous user sees that his comment was deleted.
  cache_clear_all();
  $commands[] = ajax_command_remove('#commentz-inner-' . $commentz['cid']);
  // Custom command.
  $commands[] = array('command' => 'updateCommentzCounter');
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Comment Form.
 */
function commentz_form($form, $form_state, $node) {
  $form['#node'] = $node;
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => "",
    '#rows' => 2,
    '#attributes' => array('placeholder' => t('Enter comment'), 'id' => 'commentz-textarea')
  );

  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  $form['pid'] = array(
    '#type' => 'value',
    '#value' => 0,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => "Comment",
    '#ajax' => array(
      'callback' => 'commentz_form_submit',
      'wrapper' => 'commentz-wrapper',
      'method' => 'append',
      'effect' => 'fade',
    ),
    '#attributes' => array('class' => array('btn-primary')),
  );
  return $form;
}


function commentz_prepare_submit($form, &$form_state) {
  global $user, $language;

  $commentz = new stdClass;

  $commentz->uid = $user->uid;
  $commentz->name = $user->name;
  $commentz->mail = $user->mail;
  // @todo set proper language
  $commentz->language = LANGUAGE_NONE;
  $commentz->changed = REQUEST_TIME;
  if ($cid = $form_state['values']['cid']) {
    $commentz->cid = $cid;
    $commentz->is_new = FALSE;
  } else {
    $commentz->created = REQUEST_TIME;
  }

  if ($pid = $form_state['values']['pid'])
    $commentz->pid = $pid;
  else
    $commentz->pid = 0;

  $commentz->nid = $form_state['values']['nid'];
  $commentz->body = $form_state['values']['body'];
  return $commentz;
}

function commentz_form_validate($form, &$form_state) {
  if (empty($form_state['values']['body'])) {
    form_set_error('body', '');
  }
}

function commentz_form_submit(&$form, &$form_state) {

  if (form_get_errors()) {
    return;
  }

  $node = $form['#node'];
  $commentz = commentz_prepare_submit($form, $form_state);
  $commentz_wrapper = commentz_save($commentz);
  $commentz = commentz_load($commentz_wrapper->cid->value());

  $commentz_build = commentz_view($commentz, $node);
  $commentz_html = drupal_render($commentz_build);
  $commands[] = ajax_command_append('.commentz-section', $commentz_html);
  $commands[] = ajax_command_invoke('#commentz-textarea', 'val', array(""));
  return array('#type' => 'ajax', '#commands' => $commands);
}

function commentz_edit_form($form, $form_state, $cid) {

   $form_build = commentz_form();
   $commentz = commentz_load($cid);
   $node = node_load($commentz['nid']);
   $form_build = drupal_get_form('commentz_form', $node);
   $form_build['body']['#default_value'] = $commentz['body'];
   unset($form_build['body']['#value']);
   $form_build['#prefix'] = "<div class='commentz-form'>";
   $form_build['#suffix'] = "</div>";
   $form_build['submit']['#suffix'] = "<a href='javascript:;' class='commentz-edit-cancel'>" . t('Cancel') . "</a>";
   $form_build['submit']['#value'] = t('Edit');
   $form_build['cid'] = array(
     '#type' => 'value',
     '#value' => $cid,
   );
   $form_build['submit']['#ajax']['callback'] = 'commentz_edit_form_submit';
   return $form_build;
}

function commentz_edit_form_submit(&$form, &$form_state) {

  $node = $form['#node'];
  $cid = $form_state['values']['cid'];
  $commentz = commentz_prepare_submit($form, $form_state);
  $commentz_wrapper = commentz_save($commentz);

  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-content", 'html', array($form_state['values']['body']));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-content", 'addClass', array('show'));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-content", 'removeClass', array('hide'));

  $commands[] = ajax_command_remove('#commentz-inner-' . $cid . " .commentz-form");

  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links", 'removeClass', array('hide'));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links", 'addClass', array('show'));

  return array('#type' => 'ajax', '#commands' => $commands);
}

function commentz_response_form($form, $form_state, $commentz) {
  $form = array();
  $form['#commentz'] = $commentz;
  $form['#id'] = 'commentz-response-form-' . $commentz['cid'];
  $form['#prefix'] = "<div class='commentz-response-inner hide commentz-response-form'>";
  $form['response'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('Add a reply'), 'class' => array('commentz-response-textfield')),
    '#id' => 'commentz-response-input-' . $commentz['cid'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Reply'),
    '#ajax' => array(
      'callback' => 'commentz_response_form_submit',
      'wrapper' => 'commentz-response-wrapper',
      'method' => 'append',
      'effect' => 'fade',
    ),
  );

  $form['#suffix'] = "</div>";
  return $form;
}

function commentz_response_form_validate($form, &$form_state) {
  if (empty($form_state['values']['response'])) {
    form_set_error('response', '');
  }
}

function commentz_response_form_submit(&$form, &$form_state) {
  if (form_get_errors()) {
    return;
  }

  $commentz = $form['#commentz'];
  $response = new stdClass;
  $response->pid = $commentz['cid'];
  $response->body = $form_state['values']['response'];
  $response->created = REQUEST_TIME;
  $response->uid = $commentz['uid'];
  $response->changed = REQUEST_TIME;
  $response->nid = $commentz['nid'];
  $response->mail = $commentz['mail'];
  $response->language = LANGUAGE_NONE;
  $response->name = $commentz['name'];

  $response_wrapper = commentz_save($response);

  $_response = commentz_load($response_wrapper->cid->value());

  $response_build = commentz_response_view($_response);
  $response_html = drupal_render($response_build);
  $commands[] = ajax_command_append('#commentz-responses-' . $response->pid, $response_html);
  $commands[] = ajax_command_invoke('#commentz-response-input-' . $response->pid, 'val', array(""));
  return array('#type' => 'ajax', '#commands' => $commands);
}
