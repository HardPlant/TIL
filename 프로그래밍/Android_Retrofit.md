# Retrofit를 이용해 REST Client를 만드는 법

* Retrofit
    안드로이드에서 REST API를 사용하기 위한 라이브러리.

* 적용
    build.gradle에 다음 문구를 추가한다.
>compile 'com.squareup.retrofit2:retrofit:(insert latest version)'

* 소개
    interface를 정의하고, interface class를 Retrofit에 초기화하면 된다.

    GitHub의 user와 관련된 부분을 불러오려면

    - 인터페이스 정의
>public interface GitHubService {
>  @GET("users/{user}/repos")
>  Call<List<Repo>> listRepos(@Path("user") String user);
>}

    - Retrofit 초기화
>Retrofit retrofit = new Retrofit.Builder()
>    .baseUrl("https://api.github.com/")
>    .build();
>
>GitHubService service = retrofit.create(GitHubService.class);

* JSON응답 처리
    - GsonConverterFactory 라이브러리 추가

> compile 'com.squareup.retrofit2:converter-gson:(insert latest version)'

    - retrofit 초기화 코드에 addConverterFactory를 추가

>Retrofit retrofit = new Retrofit.Builder()
>    .baseUrl("https://api.github.com")
>    .addConverterFactory(GsonConverterFactory.create())
>    .build();

    - 응답 형식 만들기
        응답 형식에 대한 클래스 Repo를 만들어주면 된다.
>
public class Repo {
    String name;

    public Repo(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Repo{" +
                "name='" + name + '\'' +
                '}';
    }
}
>       
* 실행
    service 인터페이스를 가져온 다음, enqueue로 콜백을 등록한다.
>
            Call<List<Repo>> repos = service.listRepos("octocat");
        repos.enqueue(new Callback<List<Repo>>() {
            @Override
            public void onResponse(Call<List<Repo>> call, Response<List<Repo>> response) {
                textView.setText(response.body().toString());
            }

            @Override
            public void onFailure(Call<List<Repo>> call, Throwable t) {

            }
        });
>
    함수 호출 시, 자동으로 콜이 실행된다.

* Full Source
    - 호출 부분
>
        public void getUser(){
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("https://api.github.com")
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        GitHubService service = retrofit.create(GitHubService.class);

        Call<List<Repo>> repos = service.listRepos("octocat");
        repos.enqueue(new Callback<List<Repo>>() {
            @Override
            public void onResponse(Call<List<Repo>> call, Response<List<Repo>> response) {
                textView.setText(response.body().toString());
            }

            @Override
            public void onFailure(Call<List<Repo>> call, Throwable t) {

            }
        });
    }
>    
    - Retrofit 인터페이스 선언 부분
>
public interface GitHubService {
    @GET("users/{user}/repos")
    Call<List<Repo>> listRepos(@Path("user") String user);
}
>
    - 데이터 객체
>
public class Repo {
    String name;

    public Repo(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Repo{" +
                "name='" + name + '\'' +
                '}';
    }
}
>