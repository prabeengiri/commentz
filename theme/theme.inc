<?php
/**
 * @file
 * There definition and preprocess
 */
/**
 * Implements hook_theme().
 */
function commentz_theme($existing, $type, $theme, $path) {
  return array(
    'commentz' => array(
      'template' => 'theme/commentz',
      'render element' => 'commentz'
    ),
    'commentz_wrapper' => array(
      'template' => 'theme/commentz-wrapper',
      'render element' => 'commentz_wrapper'
    ),
    'commentz_response' => array(
      'template' => 'theme/commentz-response',
      'render element' => 'commentz_response'
    ),
    'commentz_response_delete_link' => array(
      'variables' => array('response_id' => NULL)
    ),
  );
}

/**
 * Implement preprocess comment wrapper.
 */
function commentz_preprocess_commentz_wrapper(&$variables, $hook) {
  $variables['count'] = $variables['commentz_wrapper']['commentzs']['#count'];
  $variables['commentzs'] = $variables['commentz_wrapper']['commentzs'];
  $variables['commentz_form'] = user_is_logged_in() ?
    $variables['commentz_wrapper']['commentz_form'] :
    l("Login to comment", "user/login",
    array('query' => array(
      'destination' => drupal_get_path_alias($_GET['q']) . "#add-comment",
    )));
}

function commentz_preprocess_commentz(&$variables, $hook) {

  $comment = $variables['commentz']['#comment'];
  $interval = time() - $comment['created'];
  $variables['comment']['created'] = '' . format_interval($interval, 1) . t(' ago');
  unset($variables['elements']['#comment']);
  $variables['comment']['author'] = l($comment['name'], "user/" . $comment['uid']);
  $variables['comment']['avatar'] = commentz_get_avatar($comment['uid']);
  $variables['comment']['comment_id'] = $comment['cid'];
  $variables['comment']['content'] = $comment['body'];
  $variables['comment']['links'] = $variables['commentz']['links'];

  $responses = isset($variables['commentz']['commentz_responses']) ? $variables['commentz']['commentz_responses'] : array();
  $variables['comment']['responses'] = $responses;

}

function commentz_preprocess_commentz_response(&$variables) {
  $response = $variables['commentz_response']['#response'];

  $interval = time() - $response['created'];
  $variables['created'] = '' . format_interval($interval, 1) . t(' ago');
  $variables['author'] = l($response['name'], 'user/' . $response['uid']);
  $variables['response'] = $response['body'];
  $variables['comment_id'] = $response['cid'];
  $variables['delete_link'] = $variables['commentz_response']['#delete_link'];
}

function theme_commentz_response_delete_link($variables) {
  return '<a href="' . base_path() . 'commentz/response/' . $variables['response_id'] . '/delete" class="use-ajax commentz-response-delete-link"><span class="glyphicon glyphicon-remove" aria-hidden="true"></span></a>';
}
