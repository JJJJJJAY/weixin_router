<?php

/**
 * @file
 * weixin wangxb actions
 */

class WangxbBaseAction extends WeixinAction implements WeixinActionInterface {
  protected function _initResponse() {
    $response = $this->getResponse();

    $fromUserName = $this->getRequest()->getParam('FromUserName');
    $toUserName = $this->getRequest()->getParam('ToUserName');

    $response->fromUserName = $toUserName;
    $response->toUserName = $fromUserName;
  }

  public function execute() {
    $this->_initResponse();
  }
}

/**
 * Subscribe action
 */
class WangxbSubscribeAction extends WangxbBaseAction implements WeixinActionInterface {
  public function execute() {
    parent::execute();
    $response->content = "hello $fromUserName, thank you for subcribe my weixin";
  }
}

/**
 * Unsubscribe action
 */
class WangxbUnsubscribeAction extends WeixinAction implements WeixinActionInterface {
  public function execute() {
    watchdog('weixin', 'user %username unsubscribe your weixin MP.', array('%username' => $fromUserName));
  }
}

/**
 * Default action, return command list
 */
class WangxbDefaultAction extends WangxbBaseAction implements WeixinActionInterface {
  public function execute() {
    parent::execute();

    // get all event callback information
    $actions = module_invoke_all('weixin_router_actions');
    if (empty($actions)) {
      return FALSE;
    }

    $output = '';
    $snippet = "[%s]: %s";

    foreach ($actions as $eventCode => $action) {
      if ($action['type'] == WEIXIN_ROUTER_TYPE_TEXT) {
        $output .= sprintf($snippet, $eventCode, $action['description']);
      }
    }
    $this->getResponse()->content = $output;
  }
}
