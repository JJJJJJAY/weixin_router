<?php

/**
 * @file
 * The actions implements
 */
class HelloAction extends WeixinAction {
  public function execute() {
    $response = $this->getResponse();

    $fromUserName = $this->getRequest()->getParam('FromUserName');
    $toUserName = $this->getRequest()->getParam('ToUserName');

    $response->content = "hello $fromUserName";
    $response->fromUserName = $toUserName;
    $response->toUserName = $fromUserName;
  }
}
