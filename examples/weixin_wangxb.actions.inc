<?php

/**
 * @file
 * weixin wangxb actions
 */

/**
 * Subscribe action
 */
class WangxbSubscribeAction extends WeixinAction {
  public function execute() {
    $response = $this->getResponse();

    $fromUserName = $this->getRequest()->getParam('FromUserName');
    $toUserName = $this->getRequest()->getParam('ToUserName');

    $response->content = "hello $fromUserName, thank you for subcribe my weixin";
    $response->fromUserName = $toUserName;
    $response->toUserName = $fromUserName;
  }
}

/**
 * Unsubscribe action
 */
class WangxbUnsubscribeAction extends WeixinAction {
  public function execute() {
    watchdog('weixin', 'user %username unsubscribe your weixin MP.', array('%username' => $fromUserName));
  }
}
