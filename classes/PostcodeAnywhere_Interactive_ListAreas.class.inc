<?php

/*

  @file
    PostcodeAnywhere Interactive ListAreas (v1.00)

  Lists the postcode areas in the UK.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAreas/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAreas/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAreas/v1.00/json3.ws?Key=AA11-AA11-AA11-AA11&UserName=David
  Sample response: {"Items":[{"Id":"AB","PostcodeArea":"AB","Name":"Aberdeen"},{"Id":"AL","PostcodeArea":"AL","Name":"St Albans"},{"Id":"B","PostcodeArea":"B","Name":"Birmingham"},{"Id":"BA","PostcodeArea":"BA","Name":"Bath"},{"Id":"BB","PostcodeArea":"BB","Name":"Blackburn"},{"Id":"BD","PostcodeArea":"BD","Name":"Bradford"},{"Id":"BH","PostcodeArea":"BH","Name":"Bournemouth"},{"Id":"BL","PostcodeArea":"BL","Name":"Bolton"},{"Id":"BN","PostcodeArea":"BN","Name":"Brighton"},{"Id":"BR","PostcodeArea":"BR","Name":"Bromley"},{"Id":"BS","PostcodeArea":"BS","Name":"Bristol"},{"Id":"BT","PostcodeArea":"BT","Name":"Belfast"},{"Id":"CA","PostcodeArea":"CA","Name":"Carlisle"},{"Id":"CB","PostcodeArea":"CB","Name":"Cambridge"},{"Id":"CF","PostcodeArea":"CF","Name":"Cardiff"},{"Id":"CH","PostcodeArea":"CH","Name":"Chester"},{"Id":"CM","PostcodeArea":"CM","Name":"Chelmsford"},{"Id":"CO","PostcodeArea":"CO","Name":"Colchester"},{"Id":"CR","PostcodeArea":"CR","Name":"Croydon"},{"Id":"CT","PostcodeArea":"CT","Name":"Canterbury"},{"Id":"CV","PostcodeArea":"CV","Name":"Coventry"},{"Id":"CW","PostcodeArea":"CW","Name":"Crewe"},{"Id":"DA","PostcodeArea":"DA","Name":"Dartford"},{"Id":"DD","PostcodeArea":"DD","Name":"Dundee"},{"Id":"DE","PostcodeArea":"DE","Name":"Derby"},{"Id":"DG","PostcodeArea":"DG","Name":"Dumfries and Galloway"},{"Id":"DH","PostcodeArea":"DH","Name":"Durham"},{"Id":"DL","PostcodeArea":"DL","Name":"Darlington"},{"Id":"DN","PostcodeArea":"DN","Name":"Doncaster"},{"Id":"DT","PostcodeArea":"DT","Name":"Dorchester"},{"Id":"DY","PostcodeArea":"DY","Name":"Dudley"},{"Id":"E","PostcodeArea":"E","Name":"London - East"},{"Id":"EC","PostcodeArea":"EC","Name":"London - East Central"},{"Id":"EH","PostcodeArea":"EH","Name":"Edinburgh"},{"Id":"EN","PostcodeArea":"EN","Name":"Enfield"},{"Id":"EX","PostcodeArea":"EX","Name":"Exeter"},{"Id":"FK","PostcodeArea":"FK","Name":"Falkirk"},{"Id":"FY","PostcodeArea":"FY","Name":"Blackpool"},{"Id":"G","PostcodeArea":"G","Name":"Glasgow"},{"Id":"GL","PostcodeArea":"GL","Name":"Gloucester"},{"Id":"GU","PostcodeArea":"GU","Name":"Guildford"},{"Id":"GY","PostcodeArea":"GY","Name":"Guernsey"},{"Id":"HA","PostcodeArea":"HA","Name":"Harrow"},{"Id":"HD","PostcodeArea":"HD","Name":"Huddersfield"},{"Id":"HG","PostcodeArea":"HG","Name":"Harrogate"},{"Id":"HP","PostcodeArea":"HP","Name":"Hemel Hempstead"},{"Id":"HR","PostcodeArea":"HR","Name":"Hereford"},{"Id":"HS","PostcodeArea":"HS","Name":"Stornoway"},{"Id":"HU","PostcodeArea":"HU","Name":"Hull"},{"Id":"HX","PostcodeArea":"HX","Name":"Halifax"},{"Id":"IG","PostcodeArea":"IG","Name":"Ilford"},{"Id":"IM","PostcodeArea":"IM","Name":"Isle Of Man"},{"Id":"IP","PostcodeArea":"IP","Name":"Ipswich"},{"Id":"IV","PostcodeArea":"IV","Name":"Inverness"},{"Id":"JE","PostcodeArea":"JE","Name":"Jersey"},{"Id":"KA","PostcodeArea":"KA","Name":"Kilmarnock"},{"Id":"KT","PostcodeArea":"KT","Name":"Kingston upon Thames"},{"Id":"KW","PostcodeArea":"KW","Name":"Wick"},{"Id":"KY","PostcodeArea":"KY","Name":"Kirkcaldy"},{"Id":"L","PostcodeArea":"L","Name":"Liverpool"},{"Id":"LA","PostcodeArea":"LA","Name":"Lancaster"},{"Id":"LD","PostcodeArea":"LD","Name":"Llandrindod Wells"},{"Id":"LE","PostcodeArea":"LE","Name":"Leicester"},{"Id":"LL","PostcodeArea":"LL","Name":"Llandudno"},{"Id":"LN","PostcodeArea":"LN","Name":"Lincoln"},{"Id":"LS","PostcodeArea":"LS","Name":"Leeds"},{"Id":"LU","PostcodeArea":"LU","Name":"Luton"},{"Id":"M","PostcodeArea":"M","Name":"Manchester"},{"Id":"ME","PostcodeArea":"ME","Name":"RochesterMaidstone"},{"Id":"MK","PostcodeArea":"MK","Name":"Milton Keynes"},{"Id":"ML","PostcodeArea":"ML","Name":"Motherwell"},{"Id":"N","PostcodeArea":"N","Name":"London - North"},{"Id":"NE","PostcodeArea":"NE","Name":"Newcastle upon Tyne"},{"Id":"NG","PostcodeArea":"NG","Name":"Nottingham"},{"Id":"NN","PostcodeArea":"NN","Name":"Northampton"},{"Id":"NP","PostcodeArea":"NP","Name":"Newport"},{"Id":"NR","PostcodeArea":"NR","Name":"Norwich"},{"Id":"NW","PostcodeArea":"NW","Name":"London - North West"},{"Id":"OL","PostcodeArea":"OL","Name":"Oldham"},{"Id":"OX","PostcodeArea":"OX","Name":"Oxford"},{"Id":"PA","PostcodeArea":"PA","Name":"Paisley"},{"Id":"PE","PostcodeArea":"PE","Name":"Peterborough"},{"Id":"PH","PostcodeArea":"PH","Name":"Perth"},{"Id":"PL","PostcodeArea":"PL","Name":"Plymouth"},{"Id":"PO","PostcodeArea":"PO","Name":"Portsmouth"},{"Id":"PR","PostcodeArea":"PR","Name":"Preston"},{"Id":"RG","PostcodeArea":"RG","Name":"Reading"},{"Id":"RH","PostcodeArea":"RH","Name":"Redhill"},{"Id":"RM","PostcodeArea":"RM","Name":"Romford"},{"Id":"S","PostcodeArea":"S","Name":"Sheffield"},{"Id":"SA","PostcodeArea":"SA","Name":"Swansea"},{"Id":"SE","PostcodeArea":"SE","Name":"London - South East"},{"Id":"SG","PostcodeArea":"SG","Name":"Stevenage"},{"Id":"SK","PostcodeArea":"SK","Name":"Stockport"},{"Id":"SL","PostcodeArea":"SL","Name":"Slough"},{"Id":"SM","PostcodeArea":"SM","Name":"Sutton"},{"Id":"SN","PostcodeArea":"SN","Name":"Swindon"},{"Id":"SO","PostcodeArea":"SO","Name":"Southampton"},{"Id":"SP","PostcodeArea":"SP","Name":"Salisbury"},{"Id":"SR","PostcodeArea":"SR","Name":"Sunderland"},{"Id":"SS","PostcodeArea":"SS","Name":"Southend-on-sea"},{"Id":"ST","PostcodeArea":"ST","Name":"Stoke-on-Trent"},{"Id":"SW","PostcodeArea":"SW","Name":"London - South West"},{"Id":"SY","PostcodeArea":"SY","Name":"Shrewsbury"},{"Id":"TA","PostcodeArea":"TA","Name":"Taunton"},{"Id":"TD","PostcodeArea":"TD","Name":"Galashiels"},{"Id":"TF","PostcodeArea":"TF","Name":"Telford"},{"Id":"TN","PostcodeArea":"TN","Name":"Tunbridge Wells"},{"Id":"TQ","PostcodeArea":"TQ","Name":"Torquay"},{"Id":"TR","PostcodeArea":"TR","Name":"Truro"},{"Id":"TS","PostcodeArea":"TS","Name":"Middlesborough (Stockton-on-Tees)"},{"Id":"TW","PostcodeArea":"TW","Name":"Twickenham"},{"Id":"UB","PostcodeArea":"UB","Name":"Uxbridge"},{"Id":"W","PostcodeArea":"W","Name":"London - West"},{"Id":"WA","PostcodeArea":"WA","Name":"Warrington"},{"Id":"WC","PostcodeArea":"WC","Name":"London - West Central"},{"Id":"WD","PostcodeArea":"WD","Name":"Watford"},{"Id":"WF","PostcodeArea":"WF","Name":"Wakefield"},{"Id":"WN","PostcodeArea":"WN","Name":"Wigan"},{"Id":"WR","PostcodeArea":"WR","Name":"Worcester"},{"Id":"WS","PostcodeArea":"WS","Name":"Walsall"},{"Id":"WV","PostcodeArea":"WV","Name":"Wolverhampton"},{"Id":"YO","PostcodeArea":"YO","Name":"York"},{"Id":"ZE","PostcodeArea":"ZE","Name":"Shetland"}]}

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/listareas/1/

*/

class PostcodeAnywhere_Interactive_ListAreas
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_ListAreas($Key, $UserName)
   {
      $this->Key = $Key;
      $this->UserName = $UserName;
   }

  /**
   *
   */
  function MakeRequest() {

    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAreas/v1.00/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&UserName=" . urlencode($this->UserName);

    // Make the request to Postcode Anywhere and parse the XML returned.
    $file = simplexml_load_file($url);

    // Check for an error, if there is one then throw an exception.
    if ($file->Columns->Column->attributes()->Name == "Error") {
      throw new Exception("[ID] " . $file->Rows->Row->attributes()->Error . " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description . " [CAUSE] " . $file->Rows->Row->attributes()->Cause . " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution);
    }

    // Copy the data.
    if (!empty($file->Rows)) {
      foreach ($file->Rows->Row as $item) {
        $this->Data[] = array('Id' => $item->attributes()->Id, 'PostcodeArea' => $item->attributes()->PostcodeArea, 'Name' => $item->attributes()->Name);
      }
    }
  }

  /**
   *
   */
  function HasData() {

    if (!empty($this->Data)) {
      return $this->Data;
    }
    return FALSE;
  }

}

// Example usage
// -------------
// $pa = new PostcodeAnywhere_Interactive_ListAreas_v1_00 ("AA11-AA11-AA11-AA11","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["PostcodeArea"] . "<br/>";
//      echo $item["Name"] . "<br/>";
//   }
// }.
