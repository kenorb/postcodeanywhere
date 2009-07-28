<?php
/**
 *  @description Generate SOAP submission XML for MailBuild
 *
 *  @notes Put this in your theme's directory, to override the call in pamb.module
 *
 *  @calledBy: pamb.module, via e.g. theme('mailbuildsoap')
 *
 *  @param $a['auth'] MailBuild authentication fields
 *  @param $a['basic'] Core fields, required by MailBuild
 *  @param $a['custom'] Custom fields, configurable at MailBuild
 *
 *  @returns XML SOAP packet as text
 */
?>
<?php echo "<" . "?" ?>xml version="1.0" encoding="utf-8"<?php echo "?" . ">\n" ?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xmlns:xsd="http://www.w3.org/2001/XMLSchema"
 xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
  <soap:Body>
    <Subscriber.AddWithCustomFields xmlns="http://api.createsend.com/api/">
      <ApiKey><?php echo $auth['key'] ?></ApiKey>
      <ListID><?php echo $auth['list'] ?></ListID>
      <Email><?php echo $basic['email'] ?></Email>
      <Name><?php echo $basic['name'] ?></Name>

      <?php if (is_array($custom) && count($custom)): ?>
      <CustomFields>
        <?php foreach($custom as $ck => $cp) { ?>
        <SubscriberCustomField>
          <Key><?php echo $ck ?></Key>
          <Value><?php echo $cp ?></Value>
        </SubscriberCustomField>
        <?php } ?>
      </CustomFields>
      <?php endif; ?>

    </Subscriber.AddWithCustomFields>
  </soap:Body>
</soap:Envelope>