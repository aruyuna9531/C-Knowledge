/*
algorithm的sort的实现
用快排Partition思想给数据分块，每次确定1个元素的位置，并使得这个元素左边的任意元素与它自己满足用户定义的compare规则，且自己与右边的任意元素也满足compare规则
然后返回Partition确定位置的元素下标，这个下标把数组分为左右两部分
然后对数字较少的一边继续执行快速排序。直到一部分元素个数少于或等于16个数为止，此时使用插入排序算法。
一边快速排序后，缩小待排序范围，继续执行快速排序。

元素少于16个时改变算法的原因
从时间复杂度分析，快速排序的平均时间复杂度O(nlogn)，数据乱序时效率最高，有序时最低（降至O(n^2)），
插入排序的平均时间复杂度O(n^2)（查位置O(n)，插入操作O(n)），最好情况是升序排列，时间复杂度O(n)，因此处在快排的最坏情况时，效率优于快排。
快速排序适合大量数据，插入排序适合小型数据。在分块分到只剩16个待排序元素时，这些数据其实也基本有序，此时再使用快速排序很容易陷入最坏局面。
因此每次大分块使用快速排序，分到足够小时改用插入排序，效率是比每次都使用快速排序效率要高的。

例子：现有数据集
35 1 99 2 4 13 12 16 27 18 19 20 24 26 29 31 33 32 46 49 50 101 104 109 4 11 13 15 26 27 29 31 41 45 66 80 [71] 79 89 25 97 96 11 23 60 65 150 139 21 26 151 189 174 30 36 25 18 16 20 31 33 46 48 11 12 5 8 32 26 78 69 15 25

共有元素73个
中间位置是第37个，即71（中括号框出）
首先以此数分块，快排思想，小于71的移到左边，大于71的移到右边，Partition得到结果：
35 1 25 2 4 13 12 16 27 18 19 20 24 26 29 31 33 32 46 49 50 15 69 26 4 11 13 15 26 27 29 31 41 45 66 32 8 5 25 12 11 11 23 60 65 48 46 21 26 33 31 20 30 36 25 18 <lp 16> <fp 71> 174 189 151 139 150 96 97 89 79 80 109 78 104 101 99
此时first指针和last指针分别指向上面fp和lp的数，lp<fp，结束，返回fp的下标57（从0开始）
71的位置是准确的。
然后比较两部分的数据个数，发现后方元素共15个，比前方57个少，于是先给后方排序
然后在_Sort的for条件直接不满足，这部分执行插入排序后返回。然后last缩小到57，继续对0~57进行快排。直到结束。

*/

template<class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last)
{_Sort_0(first, last, _Val_type(first)); }

template<class RandomAccessIterator, class Compare>
inline void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{_Sort_0(first, last, comp, _Val_type(first)); }
/*
这两个是内联函数，执行sort(...)时会重定向到_Sort_0函数，会添加一个参数_Val_type
_Val_type(RandomAccessIterator)是提取一个数据类型
由于前者是后者的一种特殊形式，所以省略前者，直接分析后者的源码。comp是比较函数，需要自己定义，返回值布尔。比如
bool compare(int a, int b){
  return a>b;
}
这样在调用sort时加入这个compare，sort执行时会使用compare(a,b)这种操作
*/

template<class RandomAccessIterator, class _Ty, class Compare> inline
void _Sort_0(RandomAccessIterator first, RandomAccessIterator last, Compare comp, _Ty *)
{
	if (last - first <= _SORT_MAX)                 //原algorithm库里，_SORT_MAX=16
		_Insertion_sort(first, last, comp);            //如果排序元素个数小于等于_SORT_MAX个，那么使用插入排序算法
	else{
		_Sort(first, last, comp, (_Ty *)0);            //大于_SORT_MAX个元素时，先使用快速排序算法
		_Insertion_sort(first, first + _SORT_MAX, comp);//前_SORT_MAX个元素采用插入排序算法
		for (first += _SORT_MAX; first != last; ++first)
			_Unguarded_insert(first, _Ty(*first), comp);  //从_SORT_MAX开始到最后一个为止，采用Unguarded_insert（疑似从后往前插入排序，未验证）
	}
}
      
template<class RandomAccessIterator, class _Ty, class Compare>
inline void _Sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp, _Ty *)
{
	//快速排序（改进）
	for (; _SORT_MAX < last - first; )			//排到只剩_SORT_MAX个数以内没有排序为止（后面使用插入排序）
	{
		//快排的Partition函数，执行后会在下标_M使得任意左元素与_M满足comp规则，_M与任意右元素满足comp规则
		RandomAccessIterator _M = _Unguarded_partition(first, last, _Median(_Ty(*first),
			_Ty(*(first + (last - first) / 2)), _Ty(*(last - 1)), comp), comp);
		//如果_M离last的距离小于与first的距离，递归对从_M到最后的元素排序，然后将last值置为_M（后面已有序）
		//否则先递归对_M前面的元素排序，然后将first置为_M（前面已有序）
		if (last - _M <= _M - first)
			_Sort(_M, last, comp, _Val_type(first)), last = _M;
		else
			_Sort(first, _M, comp, _Val_type(first)), first = _M;
	}
}

template<class _Ty, class Compare>
inline _Ty _Median(_Ty _X, _Ty _Y, _Ty _Z, Compare comp)
{
    //median函数：在比较函数为comp的基础上，比较3个值里中间的那个值。比如a<b<c，将返回b
    if (comp(_X, _Y))
			return (comp(_Y, _Z) ? _Y : comp(_X, _Z) ? _Z : _X);
		else
			return (comp(_X, _Z) ? _X : comp(_Y, _Z) ? _Z : _Y);
}

template<class RandomAccessIterator, class _Ty, class Compare>
inline RandomAccessIterator _Unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, _Ty _Piv, Compare comp)
{
	//实际上正是快速排序的Partition函数思想
	for (; ; ++first)
	{
		for (; comp(*first, _Piv); ++first);    //找到第一个comp比较函数返回false的位置，该位置的前面的元素全部是小于_Piv（即中间元素）的
		for (; comp(_Piv, *--last); );			//找到最后一个comp比较函数返回true的位置，该位置的后面的元素全部是大于_Piv的
		if (last <= first)
			return (first);						//返回Partition的下标位置，该位置的左边所有元素与first元素均满足comp的规则，first与右边元素均满足comp规则
		iter_swap(first, last);					//尚未完成分配，交换这两个元素
	}
}

template<class RandomAccessIterator, class Compare> inline
void _Insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{_Insertion_sort_1(first, last, comp, _Val_type(first)); }

template<class RandomAccessIterator, class _Ty, class Compare>
inline void _Insertion_sort_1(RandomAccessIterator first, RandomAccessIterator last, Compare comp, _Ty *)
{
	//插入排序（改进）
	if (first != last)					//如果first=last那么只有1个元素直接就不用排
		for (RandomAccessIterator _M = first; ++_M != last; )
		{
			_Ty _V = *_M;				//提取_M元素
			if (!comp(_V, *first))		//_V与first所指元素不满足comp规则时
				_Unguarded_insert(_M, _V, comp);	//对_M和_V执行_ungarded_insert
			else
			{
				copy_backward(first, _M, _M + 1);	//满足的话，需要插入，腾一下空间（把first到_M的元素各自后移1位）
				*first = _V;						//first指向元素设为_V（插入操作）
			}
		}
}
template<class RandomAccessIterator, class _Ty, class Compare>
inline void _Unguarded_insert(RandomAccessIterator last, _Ty _V, Compare comp)
{
	//_ungarded_insert：
	for (RandomAccessIterator _M = last; comp(_V, *--_M); last = _M)
		*last = *_M;	//_M从最后一个开始，每次如果_V的值和_M（自减1后）所对应元素的符合comp规则，就把_M那个元素复制给它后面
	*last = _V;			//直到第一次不满足comp规则，把_V插入此处。可保证_V与其后的元素全部满足comp规则。
}
