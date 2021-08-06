#include <WiFi.h>
#include <HTTPClient.h>
#include "data.h" //only for privacy reasons

const char *ssid = ssid_private;         //"YOUR SSID HERE"
const char *password = password_private; //"YOUR PASSWORD HERE"

char *addtoQueue_Body = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:AddURIToQueue xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID>\n<EnqueuedURI>https://bigsoundbank.com/UPLOAD/mp3/2365.mp3</EnqueuedURI><EnqueuedURIMetaData></EnqueuedURIMetaData><DesiredFirstTrackNumberEnqueued></DesiredFirstTrackNumberEnqueued><EnqueueAsNext>true</EnqueueAsNext><FirstTrackNumberEnqueued></FirstTrackNumberEnqueued><NumTracksAdded></NumTracksAdded><NewQueueLength></NewQueueLength></u:AddURIToQueue></s:Body></s:Envelope>";
char *Play_Body = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:AddURIToQueue xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID>\n<EnqueuedURI>https://bigsoundbank.com/UPLOAD/mp3/2365.mp3</EnqueuedURI><EnqueuedURIMetaData></EnqueuedURIMetaData><DesiredFirstTrackNumberEnqueued></DesiredFirstTrackNumberEnqueued><EnqueueAsNext>true</EnqueueAsNext><FirstTrackNumberEnqueued></FirstTrackNumberEnqueued><NumTracksAdded></NumTracksAdded><NewQueueLength></NewQueueLength></u:AddURIToQueue></s:Body></s:Envelope>";

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
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin("http://192.168.178.28:1400/MediaRenderer/AVTransport/Control");
        http.addHeader("Content-Type", "text/xml");
        http.addHeader("SOAPACTION", "\"urn:schemas-upnp-org:service:AVTransport:1#AddURIToQueue\"");
        int httpCode = http.POST(query);
        if (httpCode > 0)
        {
            String payload = http.getString();
            Serial.println(httpCode);
        }
        else
        {
            Serial.println("ERROR!");
        }
    }
    delay(5000);
}

void addtoQueue(){
    HTTPClient http;
        http.begin("http://192.168.178.28:1400/MediaRenderer/AVTransport/Control");
        http.addHeader("Content-Type", "text/xml");
        http.addHeader("SOAPACTION", "\"urn:schemas-upnp-org:service:AVTransport:1#AddURIToQueue\"");
        int httpCode = http.POST(addtoQueue_Body);
        if (httpCode > 0)
        {
            String payload = http.getString();
            Serial.println(httpCode);
        }
        else
        {
            Serial.println("ERROR!");
        }
}