#include <WiFi.h>
#include <HTTPClient.h>
#include "data.h" //only for privacy reasons

const char *ssid = ssid_private;         //"YOUR SSID HERE"
const char *password = password_private; //"YOUR PASSWORD HERE"

char *addtoQueue_Body = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetAVTransportURI xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID>\n<CurrentURI>https://bigsoundbank.com/UPLOAD/mp3/2365.mp3</CurrentURI><CurrentURIMetaData></CurrentURIMetaData></u:SetAVTransportURI></s:Body></s:Envelope>";
char *Play_Body = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:Play xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><Speed>1</Speed></u:Play></s:Body></s:Envelope>";

void initWiFi()
{
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(57600);
    initWiFi();
}

void loop()
{
    setAVTransportURI();
    play();
    delay(30000);
}

void setAVTransportURI(){
    HTTPClient http;
    http.begin("http://192.168.178.28:1400/MediaRenderer/AVTransport/Control");
    http.addHeader("Content-Type", "text/xml");
    http.addHeader("SOAPACTION", "\"urn:schemas-upnp-org:service:AVTransport:1#SetAVTransportURI\"");
    int httpCode = http.POST(addtoQueue_Body);
    if (httpCode > 0)
    {
        String payload = http.getString();
        Serial.println(httpCode);
    }
    else
    {
        Serial.println("ERROR couldn't add to queue!");
    }
}

void play(){
    HTTPClient http;
    http.begin("http://192.168.178.28:1400/MediaRenderer/AVTransport/Control");
    http.addHeader("Content-Type", "text/xml");
    http.addHeader("SOAPACTION", "\"urn:schemas-upnp-org:service:AVTransport:1#Play\"");
    int httpCode = http.POST(Play_Body);
    if (httpCode > 0)
    {
        String payload = http.getString();
        Serial.println(httpCode);
    }
    else
    {
        Serial.println("ERROR couldn't play!");
    }
}