<?php

/**
 * @file
 * weixin wangxb actions
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
