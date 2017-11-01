* Django REST Response

import json

from django.http import HttpResponse

response_data = {}
response_data['result'] = 'error'
response_data['message'] = 'Some error message'

return HttpResponse(json.dumps(response_data), content_type="application/json")

- Django 1.7+

from django.http import JsonResponse
return JsonResponse({'foo':'bar'})