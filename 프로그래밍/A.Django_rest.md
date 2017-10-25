* Django REST Response

import json

from django.http import HttpResponse

response_data = {}
response_data['result'] = 'error'
response_data['message'] = 'Some error message'