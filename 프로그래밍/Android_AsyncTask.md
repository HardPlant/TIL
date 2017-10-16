#AsyncTask 이용하기
Thread와 Handler를 이용할 때는 불가능했던 UI 수정이 가능해진다.

public class MatcherTask extends AsyncTask<인자타입, 진행타입, 결과타입> {
    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }

    @Override
    protected Matcher.Result doInBackground(Boolean... booleans) {
        return null;
    }

    @Override
    protected void onPostExecute(Matcher.Result result) {
        super.onPostExecute(result);
    }

인자타입은 doInBackground의 변수 종류,
진행타입은 onProgressUpdate()의 변수 종류,
결과타입은 onPostExecute()에서 사용할 변수종류이다.

- 실행
    인자타입이 Integer이면,
    MyAsyncTask mProcessTask = new MyAsyncTask();
    mProcessTask.execute(10);

- 진행
    doInBackground()에서 publishProgress(20)을 사용하면
    onProgressUpdate()에 20이 들어오며 메소드가 호출된다.
    여기서 메인 메소드에 UI작업을 시킬 수 있따.
- 리턴
    doInBackground()에서 작업 완료 후 반환할 값이다. get()을 사용해 받아올 수 있다.

- 주의사항
    execute(20);처럼 한 값만 넣어도 doInBackground()에서 값을 찾을 땐 integers[0]처럼 배열로 찾아야 한다.

