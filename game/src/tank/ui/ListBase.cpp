// ListBase.cpp

#include "stdafx.h"
#include "ListBase.h"

namespace UI
{

ListDataSourceDefault::ListDataSourceDefault()
  : _listener(NULL)
{
}

void ListDataSourceDefault::AddListener(ListDataSourceListener *cb)
{
	_listener = cb;
}

void ListDataSourceDefault::RemoveListener(ListDataSourceListener *cb)
{
	assert(_listener == cb);
	_listener = NULL;
}

int ListDataSourceDefault::GetItemCount() const
{
	return (int) _items.size();
}

int ListDataSourceDefault::GetSubItemCount(int index) const
{
	return _items[index].text.size();
}

ULONG_PTR ListDataSourceDefault::GetItemData(int index) const
{
	assert(index >= 0);
	return _items[index].data;
}

const string_t& ListDataSourceDefault::GetItemText(int index, int sub) const
{
	assert(index >= 0 && index < (int) _items.size());
	assert(sub >= 0 && sub < (int) _items[index].text.size());
	return _items[index].text[sub];
}

int ListDataSourceDefault::FindItem(const string_t &text) const
{
	for( size_t i = 0; i < _items.size(); ++i )
	{
		if( _items[i].text[0] == text )
		{
			return i;
		}
	}
	return -1;
}

int ListDataSourceDefault::AddItem(const string_t &str, UINT_PTR data)
{
	Item i;
	i.text.push_back(str);
	i.data = data;
	_items.push_back(i);

	if( _listener )
		_listener->OnAddItem();

	return _items.size() - 1;
}

void ListDataSourceDefault::SetItemText(int index, int sub, const string_t &str)
{
	assert(index >= 0 && index < (int) _items.size());
	if( sub >= (int) _items[index].text.size() )
		_items[index].text.insert(_items[index].text.end(), 1+sub - _items[index].text.size(), "");
	_items[index].text[sub] = str;
}

void ListDataSourceDefault::SetItemData(int index, ULONG_PTR data)
{
	assert(index >= 0);
	_items[index].data = data;
}

void ListDataSourceDefault::DeleteItem(int index)
{
	_items.erase(_items.begin() + index);
	if( _listener )
		_listener->OnDeleteItem(index);
}

void ListDataSourceDefault::DeleteAllItems()
{
	_items.clear();
	if( _listener )
		_listener->OnDeleteAllItems();
}

void ListDataSourceDefault::Sort()
{
	struct helper
	{
		static bool compare(const Item &left, const Item &right)
		{
			return left.text < right.text;
		}
	};
	std::sort(_items.begin(), _items.end(), &helper::compare);
}


} // end of namespace UI
// end of file
