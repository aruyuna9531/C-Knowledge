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
			_Unguarded_insert(first, _Ty(*first), comp);  //从_SORT_MAX开始到最后一个为止，采用Unguarded_insert（疑似倒序插入排序，未验证）
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
