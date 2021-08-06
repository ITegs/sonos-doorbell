""" This file send a play command to a Sonos device """

import requests

IP = '192.168.178.28'
ACTION = '"urn:schemas-upnp-org:service:AVTransport:1#AddURIToQueue"'
ENDPOINT = '/MediaRenderer/AVTransport/Control'
BODY = '''
<s:Envelope xmlns:s="http://schemas.xmlsoap.org/soap/envelope/"
 s:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">
  <s:Body>
    <u:AddURIToQueue xmlns:u="urn:schemas-upnp-org:service:AVTransport:1">
      <InstanceID>0</InstanceID>
      <EnqueuedURI>https://bigsoundbank.com/UPLOAD/mp3/2365.mp3</EnqueuedURI>
      <EnqueuedURIMetaData></EnqueuedURIMetaData>
      <DesiredFirstTrackNumberEnqueued></DesiredFirstTrackNumberEnqueued>
      <EnqueueAsNext>true</EnqueueAsNext>
      <FirstTrackNumberEnqueued></FirstTrackNumberEnqueued>
      <NumTracksAdded></NumTracksAdded>
      <NewQueueLength></NewQueueLength>
    </u:AddURIToQueue>
  </s:Body>
</s:Envelope>
'''

HEADERS = {
    'Content-Type': 'text/xml',
    'SOAPACTION': ACTION
}

URL = 'http://{ip}:1400{endpoint}'.format(ip=IP, endpoint=ENDPOINT)

REQ = requests.post(URL, data=BODY, headers=HEADERS)

print("Response:")
print(REQ.content)
