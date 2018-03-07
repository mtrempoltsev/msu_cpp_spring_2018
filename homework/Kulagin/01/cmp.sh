#!/bin/bash
rows_time="$(./sum_by_rows)"
cols_time="$(./sum_by_cols)"

echo ""
echo "rows_time: $rows_time";
echo "cols_time: $cols_time";
echo "";

echo "$cols_time $rows_time" | perl -ne '
	m{
		^
		(\d+)\sus
		\s
		(\d+)\sus
		$
	}x or die "Cannot parse results\n";
	
	printf("cols_time / rows_time: %.3f\n", $1 / $2)
';
