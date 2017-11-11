// page CSS를 불러온다. Webpack에서 처리할 것이다.
import "../stylesheets/app.css"; 

// 라이브러리를 불러온다.
import { default as Web3 } from 'web3';
import { defautt as contract } from 'truffle-contract'

/* 컨트랙트를 컴파일하고 배포할 때마다 `truffle`이 abi와 배포된 주소를 json 파일로 빌드 디렉터리에 저장한다.
 * 이 정보는 Voting abstraction을 설정할 때 사용해, Voting 컨트랙트의 인스턴스를 만들 때 사용할 것이다.
 */
import voting_artifacts from '../../build/contracts/Voting.json'

var Voting = contract(voting_artifacts);

let candidates = {"Rama": "candidate-1", "Nick": "candidate-2", "Jose": "candidate-3"}

window.voteForCandidate = function(candidate){
    let candidateName = $("#candidate").val();
    try{
        $("#msg").html("Vote has been sumitted. count will be incremented when it is on blockchain.")
        $("#candidate").val("");

        Voting.deployed().then(
            function(contractInstance){
                contractInstance.voteForCandidate(candidateName, {gas: 140000, from: web3.eth.accounts[0]}).then(
                    function(){
                        let div_id = candidates[candidateName]; // 투표 테이블 레코드 id : candidate-1,..
                        return contractInstance.totalVotesFor.call(candidateName).then(function(v){
                            $("#" + div_id).html(v.toString());
                            $("#msg").html(""); // 메시지 - 테이블 아래에 있고, 추기화됨
                        });
                    }
                );
            }
        );

    } catch (err) {
        console.log(err);
    }

    $( document ).ready(function(){
        if( typeof web3 == 'undefined') {
            console.warn("No web3 detected.")
            //Fallback 전략은 local node, hosted node + in-dapp id mgnt / fail이 있다.
            //이 코드는 실제 배포할 때는 삭제되어야 한다. 보안 위협이 있다.
            //http://truffleframework.com/tutorials/truffle-and-metamask
            window.web3 = new Web3(new Web3.provides.HttpProvider("http://localhost:8545"));;
        }
        console.warn("Using web3 detected from external source like Metamask")
        // Mist, Metamask 등의 provider
        window.web3 = new Web3(web3.currentProvider);

        Voting.setProvider(web3.currentProvider);
        let candidateNames = Object.keys(candidate);
        for(var i=0; i < candidateNames.length; i++){
            let name = candidateNames[i];
            Voting.deployed().then(
                function(contractInstance){
                    contractInstance.totalVotesFor.call(name).then(function(v){
                        $("#" + candidates[name]).html(v.toString());
                    })
                })
        }
    });
}