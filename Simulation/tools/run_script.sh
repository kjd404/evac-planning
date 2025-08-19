#!/bin/bash
for i in {0..9}
do
    time ./sim < boise/boise.slang > "boiseOut$i.txt" &
done

time ./ sim < tests/safety.slang > safetyOut.txt &
time ./ sim < tests/safety2.slang > safetyOut2.txt &
time ./ sim < tests/safety2.2.slang > safetyOut2.2.txt &

time ./ sim < tests/capacity.slang > capacityOut.txt &
time ./ sim < tests/capacity2.slang > capacityOut2.txt &
time ./ sim < tests/capacity2.2.slang > capacityOut2.2.txt &

time ./ sim < tests/agents.slang > agentsOut.txt &
time ./ sim < tests/agents2.slang > agentsOut2.txt &
time ./ sim < tests/agents2.2.slang > agentsOut2.2.txt &

time ./ sim < tests/topolgy.slang > topologyOut.txt &
time ./ sim < tests/topolgy2.slang > topologyOut2.txt
python strip_probs.py
time ./ sim < tests/topolgy2.2.slang > topologyOut2.2.txt &
