if [ "$#" -ne 2 ]; then
	echo "Usage: run_demos.sh <num_concurrent> <blocks_each>" >&2
	exit 1
fi

for ((i=0; i<$1; i++)); do
	urxvt -e ./bin/ai_demo $2&
done
