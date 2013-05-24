<?php

/**
 * @file
 * Hooks provided by the weixin_router module
 */

/**
 * Add actoins
 * @return
 *   An array of operations.
 */
function hook_weixin_router_actions() {
  return array(
    'hello' => array(
      'title' => 'hello action',
      'class' => 'HelloAction',
      'description' => 'response body is hello [FromUserName]',
      'type' => WEIXIN_ROUTER_TYPE_TEXT,
    ),
  );
}

/**
 * Alter router instance after base router loaded
 * @param $router
 *   The base router is instance of class WeixinRouter.
 */
function hook_weixin_router_alter(&$router) {
  $router->setDefaultAction(new SomeDefaultAction(WeixinRequest::load()));
}
