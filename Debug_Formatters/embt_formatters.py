import lldb
import lldb.formatters.Logger
import datetime
import re

DBG_LOG=False

# lang=38 or lang=9 --> Delphi or Pascal83

def systdatetime_SummaryProvider(valobj, dict):
	error = lldb.SBError()
	lang = int(valobj.GetFrame().GuessLanguage())
	if (lang == 38) or (lang == 9):
		dblVal = valobj.GetData().GetDouble(error, 0)
	else:	
		Ptr = valobj.address_of.Cast(valobj.GetType().GetBasicType(lldb.eBasicTypeDouble).GetPointerType());
#		val = valobj.GetChildMemberWithName('Val')
		if not Ptr.IsValid():
			return '<invalid: Ptr>'
		dblVal = Ptr.Dereference().GetData().GetDouble(error, 0)
	if error.Fail():
		return '<error:' + error.GetCString() + '>'
	# Apply offset from Delphi time base (12/30/1899) to Unix (1/1/1970)
	unixtime = (dblVal - 25569.0) * 86400
	# Handle 'negative' time by using a timedelta
	date = datetime.datetime(1970,1,1) + datetime.timedelta(seconds=unixtime)
	return date.strftime("%m/%d/%Y, %H:%M:%S")

def syscurrency_SummaryProvider(valobj, dict):
	lang = int(valobj.GetFrame().GuessLanguage())
	if (lang == 38) or (lang == 9):
		return str(valobj.GetValueAsSigned(0) / 10000)
	# in C++ the value is in an embedded 'val' member
	if DBG_LOG:
		logger >> "syscurrency_SummaryProvider for " + str(valobj.GetName())
		logger >> str(valobj);
	val = valobj.GetChildMemberWithName('Val')
	if DBG_LOG:
		logger >> "syscur val = " + str(val) + ":" + str(val.GetValueAsSigned(0))
	return str(val.GetValueAsSigned(0) / 10000)

def generic_pointer_SummaryProvider(valobj, dict):
	val = valobj.GetValueAsUnsigned(0)
	if val == 0:
		lang = int(valobj.GetFrame().GuessLanguage())
		if (lang == 38) or (lang == 9):
			return 'nil'
		else:
			return 'nullptr'
	else:
		return hex(val)

def DelphiSet_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "DelphiSet_SummaryProvider for " + str(valobj.GetName())
		logger >> str(valobj);
	# get range of elements by parsing typename
	res = re.search('.*__lldb_SET_([0-9]+)_([0-9]+)', str(valobj.GetType()))
	if not res:
		if DBG_LOG:
			logger >> '<error: bad set type: ' + str(valobj.GetType()) + '>'
		return '<error: bad set type: ' + str(valobj.GetType()) + '>'
	if DBG_LOG:
		logger >> 'min = ' + str(res.group(1))
		logger >> 'max = ' + str(res.group(2))
	# dump all bits from each byte, interpreting as integers from min
	minEl = int(res.group(1))
	lowEl = int(8 * int(minEl/8))
	maxEl = int(res.group(2))
	byteCount = int(1 + (maxEl - minEl) / 8)
	dataPtr = valobj.GetChildMemberWithName('__data')
	baseType = valobj.GetChildMemberWithName('__basetype').GetType().GetArrayElementType()
	if DBG_LOG:
		logger >> 'min = ' + str(minEl)
		logger >> 'max = ' + str(maxEl)
		logger >> 'low = ' + str(lowEl)
		logger >> 'byteCount = ' + str(byteCount)
		logger >> 'baseType = ' + str(baseType)
	error = lldb.SBError()
	result = '['
	needComma = False
	enumMmbrs = baseType.GetEnumMembers()
	if enumMmbrs.GetSize():
		for i in range(byteCount):
			val = dataPtr.GetPointeeData(i, 1)
			newchar = val.GetUnsignedInt8(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			for b in range(8):
				if (newchar & (1 << b)) == (1 << b):
					if needComma: result = result + ','
					elem = enumMmbrs.GetTypeEnumMemberAtIndex(lowEl + (i * 8) + b).GetName()
					if elem is None: elem = '??'
					result = result + elem
					needComma = True
	else:
		for i in range(byteCount):
			val = dataPtr.GetPointeeData(i, 1)
			newchar = val.GetUnsignedInt8(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			for b in range(8):
				if (newchar & (1 << b)) == (1 << b):
					if needComma: result = result + ','
					result = result + str(lowEl + (i * 8) + b)
					needComma = True
	return result + ']'


class DelphiDynArray_SynthProvider:
	def __init__(self, valobj, d):
		if DBG_LOG:
			logger >> "Init synth for a DelphiDynArray named " + str(valobj.GetName())
		self.Len = 0
		self.valobj = valobj
		
	def update(self):
		if DBG_LOG:
			logger >> "Update synth for a DelphiDynArray"
		if self.valobj.GetChildMemberWithName('__content_ptr').GetValueAsUnsigned(0) == 0:
			if DBG_LOG:
				logger >> "null __content_ptr"
			return None
		self.elementType = self.valobj.GetChildMemberWithName('__content_ptr').Dereference().GetType()
		self.Elements = self.valobj.GetChildMemberWithName('__content_ptr');
		if (int(self.valobj.GetTarget().GetAddressByteSize()) == 4):
			Ptr = self.valobj.Cast(self.valobj.GetType().GetBasicType(lldb.eBasicTypeLong).GetPointerType())
			self.Len = self.valobj.CreateValueFromAddress('f', Ptr.GetValueAsUnsigned() - 4, self.valobj.GetType().GetBasicType(lldb.eBasicTypeLong)).GetValueAsUnsigned();
		else:
			Ptr = self.valobj.Cast(self.valobj.GetType().GetBasicType(lldb.eBasicTypeLongLong).GetPointerType())
			self.Len = self.valobj.CreateValueFromAddress('f', Ptr.GetValueAsUnsigned() - 8, self.valobj.GetType().GetBasicType(lldb.eBasicTypeLongLong)).GetValueAsUnsigned();
		if DBG_LOG:
			logger >> "Array Len = " + str(self.Len)
		return False

	def num_children(self):
		if DBG_LOG:
			logger >> "Return length for a DelphiDynArray"
			logger >> str(self.Len);
		return 1 + int(self.Len)

	def get_child_index(self, name):
		if DBG_LOG:
			logger >> "child index from " + str(name)
		if name == 'length':
			return 0
		if name == 'content':
			return 0
		try:
			return 1 + int(name.lstrip('[').rstrip(']'))
		except Exception as err:
			logger >> "DelphiDynArray_SynthProvider:get_child_index exception: " + str(err)
			return None

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "Retrieving DynArray child " + str(index)
		if index < 0:
			return None
		if index == 0:
			ptr_size = self.valobj.target.addr_size
			return self.valobj.CreateValueFromData('length',\
							lldb.SBData.CreateDataFromSInt32Array(lldb.eByteOrderLittle, ptr_size, [self.Len]),\
							self.valobj.GetType().GetBasicType(lldb.eBasicTypeInt))
		if index > self.Len:
			return None
		try:
			return self.Elements.CreateChildAtOffset(
				'[' + str(index - 1) + ']', (index - 1) * self.elementType.size, self.elementType)
		except Exception as err:
			logger >> "DelphiDynArray_SynthProvider:get_child_index exception: " + str(err)
			return '<DynArray[] exception: ' + str(err) + '>'

	def has_children(self):
		if DBG_LOG:
			logger >> "has_children for a DelphiDynArray"
		return True


def DelphiString_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a DelphiString named " + str(valobj.GetName())
		logger >> str(valobj);
		logger >> str(valobj.GetValueAsUnsigned())

	Ptr = valobj.Cast(valobj.GetType().GetBasicType(lldb.eBasicTypeChar).GetPointerType())
	if DBG_LOG:
		logger >> "Ptr = " + str(Ptr)
		logger >> "Ptr-to type size = " + str(Ptr.GetType().GetPointeeType().GetByteSize())
	if Ptr.GetValueAsUnsigned() == 0:
		return "''"
	error = lldb.SBError()
	Len = valobj.CreateValueFromAddress('f', Ptr.GetValueAsUnsigned() - 4, valobj.GetType().GetBasicType(lldb.eBasicTypeInt)).GetValueAsUnsigned();
	if DBG_LOG:
		logger >> "Len = " + str(Len)
	s = u'\''
	i = 0
	while i < 2048 and i < (Len*2):
		data_val = Ptr.GetPointeeData(i, 2)
		newchar = data_val.GetUnsignedInt16(error, 0)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		if DBG_LOG:
			logger >> "char = " + hex(newchar)
		#FIXME: handle other escape chars
		if newchar != 0:
			if newchar == '\\':
				s = s + '\\'
			else:
				s = s + chr(newchar)
		else:
			break
		i += 2
	return s + u'\''
	
# See dinkumware64\xstring
def stdstring_SummaryProvider(valobj, dict):
	MyPair = valobj.GetChildMemberWithName('_Mypair')
	if not MyPair.IsValid():
		return '<invalid>'
	Myval2 = MyPair.GetChildMemberWithName('_Myval2')
	if not Myval2.IsValid():
		return '<invalid>'
	Bx = Myval2.GetChildMemberWithName('_Bx')
	if not Bx.IsValid():
		return '<invalid>'
	Size = Myval2.GetChildMemberWithName('_Mysize')
	Size = Size.GetValueAsUnsigned(0)
	# what's a good lower limit to bork on?
	if Size > 100000:
		return None
	# 16 is the cut-off for switching from inline to pointer-to storage
	if Size < 16:
		Alias = Bx.GetChildMemberWithName('_Alias')
		data = Alias.GetData()
	else:
		Ptr = Bx.GetChildMemberWithName('_Ptr')
		data = Ptr.GetPointeeData(0, Size+1)
	error = lldb.SBError()
	strval = data.GetString(error, 0)
	if error.Fail():
		return '<error:' + error.GetCString() + '>'
	else:
		return '"' + strval + '"'

def COFF_stdstring_SummaryProvider(valobj, dict):
	MyR = valobj.GetChildMemberWithName('__r_')
	if not MyR.IsValid():
		return '<Rinvalid>'
	Myval2 = MyR.GetChildMemberWithName('__value_')
	if not Myval2.IsValid():
		return '<Vinvalid>'
	MyL = Myval2.GetChildMemberWithName('__l')
	if not MyL.IsValid():
		return '<Sinvalid>'
	SizeFlag = MyL.GetChildMemberWithName('__is_long_')
	if not SizeFlag.IsValid():
		return '<SFinvalid>'
	IsLong = SizeFlag.GetValueAsUnsigned(0)
	if IsLong == 1:
		Size = MyL.GetChildMemberWithName('__size_')
		if not Size.IsValid():
			return '<SZinvalid>'
		Size = Size.GetValueAsUnsigned(0)
		if Size > 2048:
			return "''"
		Ptr = MyL.GetChildMemberWithName('__data_')
		if not Ptr.IsValid():
			return '<PTRinvalid>'
		data = Ptr.GetPointeeData(0, Size+1)
		error = lldb.SBError()
		strval = data.GetString(error, 0)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		else:
			return '"' + strval + '"'
	error = lldb.SBError()
	Ptr = valobj.address_of.Cast(valobj.GetType().GetBasicType(lldb.eBasicTypeChar).GetPointerType());
	Len = Ptr.GetPointeeData(0).GetUnsignedInt8(error, 0) / 2;
	s = u'\''
	i = 1
	while i < 2048 and i < (Len + 1):
		data_val = Ptr.GetPointeeData(i, 1)
		newchar = data_val.GetUnsignedInt8(error, 0)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		#FIXME: handle other escape chars
		if newchar != 0:
			if newchar == '\\':
				s = s + '\\'
			else:
				s = s + chr(newchar)
		else:
			break
		i += 1
	return s + u'\''

		
def stdwstring_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a wstring named " + str(valobj.GetName())
	MyPair = valobj.GetChildMemberWithName('_Mypair')
	if not MyPair.IsValid():
		return '<invalid>'
	Myval2 = MyPair.GetChildMemberWithName('_Myval2')
	if not Myval2.IsValid():
		return '<invalid>'
	Bx = Myval2.GetChildMemberWithName('_Bx')
	if not Bx.IsValid():
		return '<invalid>'
	Size = Myval2.GetChildMemberWithName('_Mysize')
	Size = Size.GetValueAsUnsigned(0)
	if Size > 100000:
		return None
	if DBG_LOG:
		logger >> "Size = " + str(Size)
	if Size < 8:
		Ptr = Bx.GetChildMemberWithName('_Buf')
	else:
		Ptr = Bx.GetChildMemberWithName('_Ptr')
	s = u'"'
	i = 0
	if DBG_LOG:
		logger >> "Ptr = " + str(Ptr)
	error = lldb.SBError()
	while i < Size:
		data_val = Ptr.GetPointeeData(i, 1)
		newchar = data_val.GetUnsignedInt16(error, 0)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		if newchar != 0:
			s = s + chr(newchar)
		i += 1
		if i > 2048:
			break
	return s + u'"'

def COFF_stdwstring_SummaryProvider(valobj, dict):
	MyR = valobj.GetChildMemberWithName('__r_')
	if not MyR.IsValid():
		return '<Rinvalid>'
	Myval2 = MyR.GetChildMemberWithName('__value_')
	if not Myval2.IsValid():
		return '<Vinvalid>'
	MyL = Myval2.GetChildMemberWithName('__l')
	if not MyL.IsValid():
		return '<Sinvalid>'
	SizeFlag = MyL.GetChildMemberWithName('__is_long_')
	if not SizeFlag.IsValid():
		return '<SFinvalid>'
	IsLong = SizeFlag.GetValueAsUnsigned(0)
	if IsLong == 1:
		Size = MyL.GetChildMemberWithName('__size_')
		if not Size.IsValid():
			return '<SZinvalid>'
		Size = Size.GetValueAsUnsigned(0)
		if Size > 2048:
			return "''"
		Ptr = MyL.GetChildMemberWithName('__data_')
		if not Ptr.IsValid():
			return '<PTRinvalid>'
		error = lldb.SBError()		
		s = u'"'
		i = 0
		while i < Size:
			data_val = Ptr.GetPointeeData(i, 1)
			newchar = data_val.GetUnsignedInt16(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			if newchar != 0:
				s = s + chr(newchar)
			i += 1
			if i > 2048:
				break
		return s + u'"'
	error = lldb.SBError()
	Ptr = valobj.address_of.Cast(valobj.GetType().GetBasicType(lldb.eBasicTypeChar16).GetPointerType());
	Len = Ptr.GetPointeeData(0).GetUnsignedInt16(error, 0) / 2;
	s = u'"'
	i = 1
	while i < 2048 and i < (Len + 1):
		data_val = Ptr.GetPointeeData(i, 2)
		newchar = data_val.GetUnsignedInt16(error, 0)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		#FIXME: handle other escape chars
		if newchar != 0:
			if newchar == '\\':
				s = s + '\\'
			else:
				s = s + chr(newchar)
		else:
			break
		i += 1
	return s + u'"'
		
def stddeque_SummaryProvider(valobj, dict):
	return valobj.GetSummary()


class stddeque_SynthProvider:

	def __init__(self, valobj, d):
		if DBG_LOG:
			logger >> "stddeque_SynthProvider __init__"
		self.valobj = valobj
		self.pointer_size = self.valobj.GetProcess().GetAddressByteSize()
		self.count = None
		try:
			self.find_block_size()
		except:
			self.block_size = -1
			self.element_size = -1
		if DBG_LOG:
			logger.write(
			 "block_size=%d, element_size=%d" %
			 (self.block_size, self.element_size))

	def find_block_size(self):
		# in order to use the deque we must have the block size
		self.element_type = self.valobj.GetType().GetTemplateArgumentType(0)
		self.element_size = self.element_type.GetByteSize()
		if self.element_size <= 1:
			self.block_size = 16
		else:
			if self.element_size <= 2:
				self.block_size = 8
			else:
				if self.element_size <= 4:
					self.block_size = 4
				else:
					if self.element_size <= 8:
						self.block_size = 2
					else:
						self.block_size = 1

	def num_children(self):
		if DBG_LOG:
			logger >> 'DEQUE num_children = ' + str(self.count)
			logger >> 'DEQUE block_size = ' + str(self.block_size)
		if self.count is None:
			return 0
		return self.count

	def has_children(self):
		return True

	def get_child_index(self, name):
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			 logger.write("DEQUE Fetching child " + str(index))
		if index < 0 or self.count is None:
			return None
		if index >= self.num_children():
			return None
		try:
			i, j = divmod(self.start + index, self.block_size)
			if DBG_LOG:
				logger >> '(i,j) = ' + str(i) + ',' + str(j)
			return self.first.CreateValueFromExpression(
				'[' + str(index) + ']', '*(*(%s + %d) + %d)' %
				(self.first.get_expr_path(), i, j))
		except Exception as err:
			logger >> "stddeque_SynthProvider:get_child_index exception: " + str(err)
			return None

	def update(self):
		try:
			Mypair = self.valobj.GetChildMemberWithName('_Mypair')
			if not Mypair.IsValid():
				self.count = None
				return None
			Myval2 = Mypair.GetChildMemberWithName('_Myval2')
			if not Myval2.IsValid():
				self.count = None
				return None
			count = Myval2.GetChildMemberWithName('_Mysize').GetValueAsUnsigned(0)
			if DBG_LOG:
				logger >> 'DEQUE count = ' + str(count)
			# we're going to limit the number displayed in any case but
			# counts greater than a reasonable amount are more likely to
			# be from uninitialized structures.
			if count > 1000000:
				self.count = None
				return None
			# give up now if we can't access memory reliably
			if self.block_size < 0:
				if DBG_LOG:
					logger.write("block_size < 0")
				return
			count = min(count, 256)
			map_ = Myval2.GetChildMemberWithName('_Map')
			start = 0 # offset?
			first = map_
			self.count = count
			self.start = start
			self.first = first
		except:
			self.count = None
			self.start = None
			self.map_first = None
			self.map_begin = None
		return None

class COFF_stddeque_SynthProvider:

	def __init__(self, valobj, d):
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider __init__ for named " + str(valobj.GetName())
		self.valobj = valobj
		self.pointer_size = self.valobj.GetProcess().GetAddressByteSize()
		self.count = None
		try:
			self.find_block_size()
		except:
			self.block_size = -1
			self.element_size = -1
		if DBG_LOG:
			logger.write("COFF_stddeque_SynthProvider block_size=%d, element_size=%d" %(self.block_size, self.element_size))

	def find_block_size(self):
		# in order to use the deque we must have the block size
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider type = " + self.valobj.GetType().GetName();
		map_ = self.valobj.GetChildMemberWithName('__map_')
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider map_ = " + str(map_)
		first_ = map_.GetChildMemberWithName('__first_')
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider first_ = " + str(first_)
		self.element_type = first_.GetType().GetPointeeType().GetPointeeType()
		self.element_size = self.element_type.GetByteSize()
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider element_type = " + self.element_type.GetName()
			logger >> "COFF_stddeque_SynthProvider element_size = " + str(self.element_size)
# from "~\include\x86_64-w64-mingw32\c++\v1\deque": sizeof(_ValueType) < 256 ? 4096 / sizeof(_ValueType) : 16;
		if self.element_size < 256:
			self.block_size = 4096 // self.element_size
		else:
			self.block_size = 16

	def num_children(self):
		if DBG_LOG:
			logger >> 'COFF_stddeque_SynthProvider num_children = ' + str(self.count)
			logger >> 'COFF_stddeque_SynthProvider block_size = ' + str(self.block_size)
		if self.count is None:
			return 0
		return self.count

	def has_children(self):
		return True

	def get_child_index(self, name):
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "COFF_stddeque_SynthProvider Fetching child " + str(index)
		if index < 0 or self.count is None:
			return None
		if index >= self.num_children():
			return None
		try:
			i, j = divmod(self.start + index, self.block_size)
			expr = '*((%s*)((((char*)(*(%s + %d))) + %d*sizeof(**(%s)))))' % ('typeof(**('+self.first.get_expr_path()+'))', self.first.get_expr_path(), i, j, self.first.get_expr_path())
			if DBG_LOG:
				logger >> 'COFF_stddeque_SynthProvider (i,j) = ' + str(i) + ',' + str(j)
				logger >> 'COFF_stddeque_SynthProvider expr = ' + expr
			return self.first.CreateValueFromExpression('[' + str(index) + ']', expr)
		except Exeception as err:
			logger >> "COFF_stddeque_SynthProvider:get_child_at_index exception: " + str(err)
			return None

	def update(self):
		try:
			count = self.valobj.GetChildMemberWithName('__size_').GetChildMemberWithName('__value_').GetValueAsUnsigned(0)
			if DBG_LOG:
				logger >> 'COFF_stddeque_SynthProvider update count = ' + str(count)
			# we're going to limit the number displayed in any case but
			# counts greater than a reasonable amount are more likely to
			# be from uninitialized structures.
			if count > 1000000:
				self.count = None
				return None
			# give up now if we can't access memory reliably
			if self.block_size < 0:
#				 logger.write("block_size < 0")
				return
			count = min(count, 256)
			map_ = self.valobj.GetChildMemberWithName('__map_')
			start = 0 # offset?
			first = map_
			self.count = count
			self.start = start
			self.first = map_.GetChildMemberWithName('__first_')
		except:
			self.count = None
			self.start = None
			self.map_first = None
			self.map_begin = None
		return None

class syststringlist_SynthProvider:
	def __init__(self, valobj, dict):
		self.valobj = valobj
		flist = self.valobj.GetChildMemberWithName('FList')
		self.base = None
		if flist.IsValid():
			self.base = flist.GetChildMemberWithName('Data')
		if DBG_LOG:
			logger >> "Providing synthetic children for a TStringList named " + (valobj.GetName())
			
	def num_children(self):
		fcount = self.valobj.GetChildMemberWithName('FCount')
		if DBG_LOG:
			logger >> "num_children = " + str(fcount.GetValueAsUnsigned(0))
		return fcount.GetValueAsUnsigned(0)
	
	def get_child_index(self, name):
		if DBG_LOG:
			logger >> "get_child_index = " + str(name)
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		if index < 0 or self.base is None:
			return None
		try:
			if DBG_LOG:
				logger >> "get_child_at_index = " + str(index)
			objType = self.base.GetType().GetPointeeType()
			offs = self.base.GetValueAsUnsigned(0) + (index * objType.GetByteSize())
			name = '[' + str(index) + ']'
			result = self.base.CreateValueFromAddress(name, offs, objType )
			result = result.GetChildMemberWithName('FString')
			return result.CreateValueFromData(name, result.GetData(), result.GetType())
		except Exception as err:
			logger >> "syststringlist_SynthProvider:get_child_at_index exception: " + str(err)
			return '<exception: ' + str(err) + '>'

	def update(self):
		flist = self.valobj.GetChildMemberWithName('FList')
		self.base = None
		if flist.IsValid():
			self.base = flist.GetChildMemberWithName('Data')
		return None
		
	def has_children(self):
		fcount = self.valobj.GetChildMemberWithName('FCount')
		return fcount.GetValueAsUnsigned(0) > 0

		
class StdVector_SynthProvider:

	class StdVectorImplementation(object):

		def __init__(self, valobj):
			self.valobj = valobj
			self.count = None

		def num_children(self):
			if self.count is None:
				self.count = self.num_children_impl()
			return self.count

		def num_children_impl(self):
			try:
				start_val = self.start.GetValueAsUnsigned(0)
				finish_val = self.finish.GetValueAsUnsigned(0)
				end_val = self.end.GetValueAsUnsigned(0)
				# Before a vector has been constructed, it will contain bad values
				# so we really need to be careful about the length we return since
				# uninitialized data can cause us to return a huge number. We need
				# to also check for any of the start, finish or end of storage values
				# being zero (NULL). If any are, then this vector has not been
				# initialized yet and we should return zero

				# Make sure nothing is NULL
				if start_val == 0 or finish_val == 0 or end_val == 0:
					return 0
				# Make sure start is less than finish
				if start_val >= finish_val:
					return 0
				# Make sure finish is less than or equal to end of storage
				if finish_val > end_val:
					return 0

				# if we have a struct (or other data type that the compiler pads to native word size)
				# this check might fail, unless the sizeof() we get is itself incremented to take the
				# padding bytes into account - on current clang it looks like
				# this is the case
				num_children = (finish_val - start_val)
				if (num_children % self.data_size) != 0:
					return 0
				else:
					num_children = num_children // self.data_size
				return num_children
			except Exception as err:
				if DBG_LOG:
					logger >> "StdVector_SynthProvider:num_children_impl: " + str(err)
				return 0

		def get_child_at_index(self, index):
			if DBG_LOG:
				logger >> "Retrieving child " + str(index)
			if index < 0:
				return None
			if index >= self.num_children():
				return None
			try:
				offset = index * self.data_size
				return self.start.CreateChildAtOffset(
					'[' + str(index) + ']', offset, self.data_type)
			except Exception as err:
				logger >> "StdVector_SynthProvider:get_child_at_index exception: " + str(err)
				return None

		def update(self):
			# preemptively setting this to None - we might end up changing our
			# mind later
			self.count = None
			try:
				# see dinkumware64\vector
				impl = self.valobj.GetChildMemberWithName('_Mypair')
				impl = impl.GetChildMemberWithName('_Myval2')
				self.start = impl.GetChildMemberWithName('_Myfirst')
				self.finish = impl.GetChildMemberWithName('_Mylast')
				self.end = impl.GetChildMemberWithName('_Myend')
				self.data_type = self.start.GetType().GetPointeeType()
				self.data_size = self.data_type.GetByteSize()
				# if any of these objects is invalid, it means there is no
				# point in trying to fetch anything
				if self.start.IsValid() and self.finish.IsValid() and self.end.IsValid() and self.data_type.IsValid():
					self.count = None
				else:
					self.count = 0
			except Exception as err:
				logger >> "StdVector_SynthProvider:update exception: " + str(err)
				pass
			return None
			
	def __init__(self, valobj, dict):
		first_template_arg_type = valobj.GetType().GetTemplateArgumentType(0)
		self.impl = self.StdVectorImplementation(valobj)
		if DBG_LOG:
			logger >> "Providing synthetic children for a vector named " + str(valobj.GetName())

	def num_children(self):
		return self.impl.num_children()

	def get_child_index(self, name):
		try:
			return int(name.lstrip('[').rstrip(']'))
		except Exception as err:
			logger >> "StdVector_SynthProvider:get_child_index exception: " + str(err)
			return -1

	def get_child_at_index(self, index):
		return self.impl.get_child_at_index(index)

	def update(self):
		return self.impl.update()

	def has_children(self):
		return True
		
class COFF_StdVector_SynthProvider:

	class COFF_StdVectorImplementation(object):

		def __init__(self, valobj):
			self.valobj = valobj
			self.count = None

		def num_children(self):
			if self.count is None:
				self.count = self.num_children_impl()
			return self.count

		def num_children_impl(self):
			if DBG_LOG:
				logger >> "COFF_Vector num_children_impl for " + str(self.valobj.GetName())
			try:
				start_val = self.start.GetValueAsUnsigned(0)
				finish_val = self.finish.GetValueAsUnsigned(0)
				end_val = self.end.GetValueAsUnsigned(0)
				if DBG_LOG:
					logger >> "COFF_Vector num_children_impl start " + str(start_val)
					logger >> "COFF_Vector num_children_impl finish " + str(finish_val)
					logger >> "COFF_Vector num_children_impl end " + str(end_val)
					logger >> "COFF_Vector num_children_impl data_size " + str(self.data_size)
				# Before a vector has been constructed, it will contain bad values
				# so we really need to be careful about the length we return since
				# uninitialized data can cause us to return a huge number. We need
				# to also check for any of the start, finish or end of storage values
				# being zero (NULL). If any are, then this vector has not been
				# initialized yet and we should return zero

				# Make sure nothing is NULL
				if start_val == 0 or finish_val == 0 or end_val == 0:
					return 0
				# Make sure start is less than finish
				if start_val >= finish_val:
					return 0
				# Make sure finish is less than or equal to end of storage
				if finish_val > end_val:
					return 0

				# if we have a struct (or other data type that the compiler pads to native word size)
				# this check might fail, unless the sizeof() we get is itself incremented to take the
				# padding bytes into account - on current clang it looks like
				# this is the case
				num_children = (finish_val - start_val)
				if (num_children % self.data_size) != 0:
					return 0
				else:
					num_children = num_children // self.data_size
				if DBG_LOG:
					logger >> "COFF_StdVector_SynthProvider:num_children_impl num_children " + str(num_children)
				return num_children
			except Exception as err:
				if DBG_LOG:
					logger >> "COFF_StdVector_SynthProvider:num_children_impl exception: " + str(err)
				return 0

		def get_child_at_index(self, index):
			if DBG_LOG:
				logger >> "Retrieving child " + str(index)
			if index < 0:
				return None
			if index >= self.num_children():
				return None
			try:
				offset = index * self.data_size
				return self.start.CreateChildAtOffset(
					'[' + str(index) + ']', offset, self.data_type)
			except Exception as err:
				if DBG_LOG:
					logger >> "COFF_StdVector_SynthProvider:get_child_at_index: " + str(err)
				return None

		def update(self):
			# preemptively setting this to None - we might end up changing our
			# mind later
			self.count = None
			try:
				if DBG_LOG:
					logger >> "COFF_Vector update for " + str(self.valobj.GetName())
				self.start = self.valobj.GetChildMemberWithName('__begin_')
				self.finish = self.valobj.GetChildMemberWithName('__end_')
				endcap = self.valobj.GetChildMemberWithName('__end_cap_')
				self.end = endcap.GetChildMemberWithName('__value_')
				self.data_type = self.start.GetType().GetPointeeType()
				self.data_size = self.data_type.GetByteSize()
				if DBG_LOG:
					logger >> "COFF_Vector update start type = " + self.data_type.GetName();
					logger >> "COFF_Vector update data_size = " + str(self.data_size);
				# if any of these objects is invalid, it means there is no
				# point in trying to fetch anything
				if self.start.IsValid() and self.finish.IsValid() and self.end.IsValid() and self.data_type.IsValid():
					self.count = None
				else:
					self.count = 0
			except Exception as err:
				logger >> "COFF_StdVector_SynthProvider:update exception: " + str(err)
				pass
			return None
			
	def __init__(self, valobj, dict):
		first_template_arg_type = valobj.GetType().GetTemplateArgumentType(0)
		if DBG_LOG:
			logger >> "Providing synthetic children for a vector named " + str(valobj.GetName())
			logger >> "COFF_Vector __init__ valobj type = " + valobj.GetType().GetName();
			logger >> "COFF_Vector __init__ template type = " + first_template_arg_type.GetName();
		self.impl = self.COFF_StdVectorImplementation(valobj)

	def num_children(self):
		return self.impl.num_children()

	def get_child_index(self, name):
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		return self.impl.get_child_at_index(index)

	def update(self):
		return self.impl.update()

	def has_children(self):
		return True		
		
def ExtractTemplateArg(typeStr, startIdx):
	endArgIdx = startIdx
	templateArgName = ''
	ac = 0
	while (endArgIdx < len(typeStr)):
		if (typeStr[endArgIdx] == '<'):
			ac += 1;
		elif (typeStr[endArgIdx] == '>'):
			if (ac == 0):
				break;
			ac -= 1
		elif (typeStr[endArgIdx] == ',') and (ac == 0):
			templateArgName = typeStr[startIdx:endArgIdx]
			break;
		endArgIdx += 1
	templateArgName = templateArgName.strip()
	#if (templateArgName.endswith('>>')):
	#	templateArgName = templateArgName[:-2] + '> >'
	#templateArgName = templateArgName.replace(', ', ',')
	return templateArgName
	
def SkipFirstArg(typeStr, startIdx):
	endArgIdx = startIdx
	ac = 0
	while (endArgIdx < len(typeStr)):
		if (typeStr[endArgIdx] == '<'):
			ac += 1;
		elif (typeStr[endArgIdx] == '>'):
			if (ac == 0):
				endArgIdx = -1
				break;
			ac -= 1
		elif (typeStr[endArgIdx] == ',') and (ac == 0):
			endArgIdx += 1
			break;
		endArgIdx += 1
	return endArgIdx
		
class COFF_StdList_SynthProvider:
	def __init__(self, valobj, dict):
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, __init__: " + valobj.name;
			logger >> "Type arg = " + valobj.GetType().name
			logger >> "Template arg = " + valobj.GetType().GetTemplateArgumentType(0).name
		typeName = valobj.GetType().name;
		resArgIdx = len('std::__1::list<')
		templateArgName = ExtractTemplateArg(typeName, resArgIdx)
		# use '!' to signal FindFirstType to not strip namespaces - PDB type entries
		# contain fully qualified names.
		templateArgName = '!' + templateArgName;
		if DBG_LOG:
			logger >> "templateArgName = " + templateArgName
		self.argType = valobj.GetFrame().GetModule().FindFirstType(templateArgName)
		if DBG_LOG:
			logger >> "templateArgType = " + str(self.argType);
		self.valobj = valobj
		self.count = -1
		
	def update(self):
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, update(self): " + valobj.name;
		try:
			# need to handle this better
			if self.count > 100000:	
				self.count = -1
			Ptr = self.valobj.GetChildMemberWithName('__end_').GetChildMemberWithName('__next_')
			if not Ptr.IsValid():
				self.count = -1
				return True
			self.count = self.valobj.GetChildMemberWithName('__size_alloc_').GetChildMemberWithName('__value_').GetValueAsUnsigned(0)
			if DBG_LOG:
				logger >> "COFF_StdList_SynthProvider, update(self): self.count" + str(self.count);
		except Exception as err:
			logger >> "COFF_StdList_SynthProvider:update: exception " + str(err)
			self.count = -1
			return True
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, update count: " + str(self.count)
		return False

	def num_children(self):
		if self.count == -1:
			if DBG_LOG:
				logger >> "COFF_StdList_SynthProvider, num_children(self): 1"
			return 1;
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, num_children(self): " + str(1 + self.count)
		return 1 + self.count

	def has_children(self):
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, has_children(self)"
		return True

	def get_child_index(self, name):
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, get_child_index: " + name
		if name == "Count":
			return 0
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			if DBG_LOG:
				logger >> "COFF_StdList_SynthProvider:get_child_index exception: " + str(err)
			return -1
		return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "COFF_StdList_SynthProvider, get_child_at_index 1: " + str(index);
		if index == 0:
			try:
				obj = self.valobj.GetChildMemberWithName('__size_alloc_').GetChildMemberWithName('__value_')
				if DBG_LOG:
					logger >> "get_child_at_index: " + str(obj.GetValueAsUnsigned(0))
				self.count = obj.GetValueAsUnsigned(0)
				if self.count > 100000:
					self.count = -1
				rv = self.valobj.CreateValueFromData('Count', obj.GetData(), obj.GetType())
				if DBG_LOG:
					logger >> "get_child_at_index: rv: " + str(rv)
				return rv
			except Exception as err:
				logger >> "COFF_StdList_SynthProvider:get_child_at_index exception 1: " + str(err)
				return '<exception: ' + str(err) + '>'
		if index > 0:
			try:
				index = index - 1
				if DBG_LOG:
					logger >> "COFF_StdList_SynthProvider, get_child_at_index > 0: " + str(index);
				nm = '[' + str(index) + ']'
				if index >= self.count:
					return None;
				Ptr = self.valobj.GetChildMemberWithName('__end_').GetChildMemberWithName('__next_')
				if DBG_LOG:
					logger >> "COFF_StdList_SynthProvider, Ptr = " + str(Ptr)
				while index > 0:
					Ptr = Ptr.GetChildMemberWithName('__next_')
					if DBG_LOG:
						logger >> "COFF_StdList_SynthProvider, Ptr = " + str(Ptr)
					index = index - 1
				Ptr = Ptr.Cast(self.valobj.GetType().GetBasicType(lldb.eBasicTypeChar).GetPointerType())
				rv = self.valobj.CreateValueFromAddress(nm, Ptr.GetValueAsUnsigned() + 16, self.argType);
				if DBG_LOG:
					logger >> "COFF_StdList_SynthProvider, get_child_at_index: rv: " + str(rv);
				return rv
			except Exception as err:
				logger >> "COFF_StdList_SynthProvider:get_child_at_index exception 2: " + str(err)
				return '<exception: ' + str(err) + '>'

def ansistring_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a ansistring named " + str(valobj.GetName())
	if valobj.GetValue() != 0:
		s = '"'
		i = 0
		newchar = -1
		Ptr = valobj.GetChildMemberWithName('Data')
		if not Ptr.IsValid():
			return '<invalid>'
		if DBG_LOG:
			logger >> "Ptr is " + str(Ptr)
		error = lldb.SBError()
		while newchar != 0:
			# read next char character out of memory
			data_val = Ptr.GetPointeeData(i, 1)
			newchar = data_val.GetUnsignedInt8(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			if newchar != 0:
				s = s + chr(newchar)
			i += 1
			if i > 2048:
				break
		s = s + '"'
	else:
		s = '<null>'
	return s
		
def ansistringT_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a ansistringT named " + str(valobj.GetName())
	if valobj.GetValue() != 0:
		i = 0
		newchar = -1
		Ptr = valobj.GetChildMemberWithName('Data')
		if not Ptr.IsValid():
			return '<invalid>'
		if DBG_LOG:
			logger >> "Ptr is " + str(Ptr)
		error = lldb.SBError()
		while newchar != 0:
			# read next char character out of memory
			data_val = Ptr.GetPointeeData(i, 1)
			size = data_val.GetByteSize()
			if DBG_LOG:
				logger >> "Size is " + str(size)
			newchar = data_val.GetUnsignedInt8(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			i += 1
			if i > 2048:
				break		#? return 'too long' ?
		if DBG_LOG:
			logger >> "length is " + str(i)
		if i == 0:
			return '""'
		data_val = Ptr.GetPointeeData(0, i)
		bytes = data_val.ReadRawData(error, 0, i-1)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		return '"%s"' % (bytes.decode('utf-8'))
	else:
		return '<null>'

def shortstring_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a shortstring named " + str(valobj.GetName())
	if valobj.GetValue() != 0:
		i = 0
		newchar = -1
		Ptr = valobj.GetChildMemberWithName('Data')
		if not Ptr.IsValid():
			return '<invalid>'
		if DBG_LOG:
			logger >> "Ptr is " + str(Ptr)
		error = lldb.SBError()
		while newchar != 0:
			# read next char character out of memory
			data_val = Ptr.GetPointeeData(i, 1)
			size = data_val.GetByteSize()
			if DBG_LOG:
				logger >> "Size is " + str(size)
			newchar = data_val.GetUnsignedInt8(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			i += 1
			if i > 2048:
				break		#? return 'too long' ?
		if DBG_LOG:
			logger >> "length is " + str(i)
		if i == 0:
			return '""'
		data_val = Ptr.GetPointeeData(0, i)
		bytes = data_val.ReadRawData(error, 0, i-1)
		if error.Fail():
			return '<error:' + error.GetCString() + '>'
		return '"%s"' % (bytes.decode('utf-8'))
	else:
		return '<null>'

		
def unicodestring_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a unicodestring named " + str(valobj.GetName())
	if valobj.GetValue() != 0:
		s = u'"'
		i = 0
		newchar = -1
		Ptr = valobj.GetChildMemberWithName('Data')
		if not Ptr.IsValid():
			return '<invalid>'
		if DBG_LOG:
			logger >> "Ptr is " + str(Ptr)
		error = lldb.SBError()
		while newchar != 0:
			# read next wchar character out of memory
			data_val = Ptr.GetPointeeData(i, 1)
			#size = data_val.GetByteSize()
			#logger >> "Size is " + str(size)
			newchar = data_val.GetUnsignedInt16(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			if newchar != 0:
				s = s + chr(newchar)
			i += 1
			if i > 2048:
				break
		s = s + u'"'
	else:
		s = '<null>'
	return s
	
def widestring_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a widestring named " + str(valobj.GetName())
	if valobj.GetValue() != 0:
		s = u'"'
		i = 0
		newchar = -1
		Ptr = valobj.GetChildMemberWithName('Data')
		if not Ptr.IsValid():
			return '<invalid>'
		if DBG_LOG:
			logger >> "Ptr is " + str(Ptr)
		error = lldb.SBError()
		while newchar != 0:
			# read next wchar character out of memory
			data_val = Ptr.GetPointeeData(i, 1)
			#size = data_val.GetByteSize()
			#logger >> "Size is " + str(size)
			newchar = data_val.GetUnsignedInt16(error, 0)
			if error.Fail():
				return '<error:' + error.GetCString() + '>'
			if newchar != 0:
				s = s + chr(newchar)
			i += 1
			if i > 2048:
				break
		s = s + u'"'
	else:
		s = '<null>'
	return s
	
class stduniqueptr_SynthProvider:
	def __init__(self, valobj, d):
		self.valobj = valobj

	def num_children(self):
		return 1

	def has_children(self):
		return True

	def get_child_index(self, name):
		if name == "_Ptr":
			return 0
		return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "get_child_at_index for a uniquePtr named " + str(self.valobj.GetName())
		if index == 0:
			try:
				obj = self.valobj.GetChildMemberWithName('_Mypair').GetChildMemberWithName('_Myval2')
				return self.valobj.CreateValueFromData('_Ptr', obj.GetData(), obj.GetType())
			except Exception as err:
				logger >> "stduniqueptr_SynthProvider:get_child_at_index exception: " + str(err)
				return '<exception: ' + str(err) + '>'
		return None
	
def stduniqueptr_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a uniquePtr named " + str(valobj.GetName())
	try:
		Ptr = valobj.GetChildMemberWithName('_Mypair').GetChildMemberWithName('_Myval2')
		if not Ptr.IsValid():
			return '<_Ptr: invalid>'
		s = str(Ptr)
		if s is None:
			s = '{...}'
		return s
	except Exception as err:
		logger >> "stduniqueptr_SummaryProvider exception: " + str(err)
		return "<exception: " + str(err) + '>'

class COFF_stduniqueptr_SynthProvider:
	def __init__(self, valobj, d):
		self.valobj = valobj

	def num_children(self):
		return 1

	def has_children(self):
		return True

	def get_child_index(self, name):
		if name == "__ptr_":
			return 0
		return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "get_child_at_index for a uniquePtr named " + str(self.valobj.GetName())
		if index == 0:
			try:
				obj = self.valobj.GetChildMemberWithName('__ptr_').GetChildAtIndex(0).GetChildMemberWithName('__value_')
				return self.valobj.CreateValueFromData('__ptr_', obj.GetData(), obj.GetType())
			except Exception as err:
				logger >> "COFF_stduniqueptr_SynthProvider:get_child_at_index exception: " + str(err)
				return '<exception: ' + str(err) + '>'
		return None
	
def COFF_stduniqueptr_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a uniquePtr named " + str(valobj.GetName())
	try:
		MyPtr = valobj
		if not MyPtr.IsValid():
			return '<__ptr_: invalid>'
		s = str(MyPtr)
		if s is None:
			s = '{...}'
		return s
	except Exception as err:
		logger >> "COFF_stduniqueptr_SummaryProvider exception: " + str(err)
		return "<exception: " + str(err) + '>'


def stdsharedptr_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a sharedPtr named " + str(valobj.GetName())
	try:
		Ptr = valobj.GetChildMemberWithName('_Ptr')
		if not Ptr.IsValid():
			return '<_Ptr: invalid>'
		error = lldb.SBError()
		Uses = valobj.GetChildMemberWithName('_Rep').GetChildMemberWithName('_Uses').GetData().GetUnsignedInt32(error, 0)
		if error.Fail():
			return '<error _Uses: ' + error.GetCString() + '>'
		Weaks = valobj.GetChildMemberWithName('_Rep').GetChildMemberWithName('_Weaks').GetData().GetUnsignedInt32(error, 0)
		if error.Fail():
			return '<error _Weaks: ' + error.GetCString() + '>'
		return str(Ptr.Dereference()) + " _Uses: " + str(Uses) + ", _Weaks: " + str(Weaks)
	except Exception as err:
		logger >> "stdsharedptr_SummaryProvider exception: " + str(err)
		return "<exception: " + str(err) + '>'
	
# override the provider in lldb source to get at the _Ptr member in dinkumware
class stdsharedptr_SynthProvider:
	def __init__(self, valobj, d):
		self.valobj = valobj

	def num_children(self):
		return 3

	def has_children(self):
		return True

	def get_child_index(self, name):
		if name == "_Ptr":
			return 0
		if name == "_Uses":
			return 1
		if name == "_Weaks":
			return 2
		return -1

	def get_child_at_index(self, index):
		if index == 0:
			return self.valobj.GetChildMemberWithName('_Ptr')
		if index == 1:
			return self.valobj.GetChildMemberWithName('_Rep').GetChildMemberWithName('_Uses')
		if index == 2:
			return self.valobj.GetChildMemberWithName('_Rep').GetChildMemberWithName('_Weaks')
		return None
		
def COFF_stdsharedptr_SummaryProvider(valobj, dict):
	if DBG_LOG:
		logger >> "Providing summary for a sharedPtr named " + str(valobj.GetName())
	try:
		Ptr = valobj.GetChildMemberWithName('__ptr_')
		if not Ptr.IsValid():
			return '<_Ptr: invalid>'
		error = lldb.SBError()
		# using an index here instead of GetChildMemberWithName means we aren't bound to the num_children limit (3)
		# since we want the 4th child.
		# see the COFF_stdsharedptr_SynthProvider class for more details.
		cntrl = valobj.GetChildAtIndex(3)
		# now we can use GetChildMemberWithName and get the correct index
		Uses = cntrl.GetChildMemberWithName('__shared_owners_').GetData().GetUnsignedInt32(error, 0)
		if error.Fail():
			return '<error _Uses:' + error.GetCString() + '>'
		Weaks = cntrl.GetChildMemberWithName('__shared_weak_owners_').GetData().GetUnsignedInt32(error, 0)
		if error.Fail():
			return '<error _Weaks: ' + error.GetCString() + '>'
		# dereferencing the pointer causes a crash.
		# also we want the pointer so debugger will format the object correctly
		rv = str(Ptr) + " _Uses: " + str(Uses) + ", _Weaks: " + str(Weaks)
		if DBG_LOG:
			logger >> rv
		return rv
	except Exception as err:
		logger >> "COFF_stdsharedptr_SummaryProvider exception: " + str(err)
		return "<exception: " + str(err) + '>'
	
class COFF_stdsharedptr_SynthProvider:
	def __init__(self, valobj, d):
		self.valobj = valobj

	def num_children(self):
		return 3

	def has_children(self):
		return True

	def get_child_index(self, name):
		if DBG_LOG:
			logger >> "COFF_stdsharedptr_SynthProvider:: get_child_index: " + name
		if name == "__ptr_":
			return 0
		if name == "__shared_owners_":
			return 1
		if name == "__shared_weak_owners_":
			return 2
		# calls to self.valobj.GetChildMemberWithName('__cntrl_').GetChildMemberWithName('__shared_owners_')
		# will actually be broken into 2 GetChildMemberWithName calls. 
		# note that there is no index for '__cntrl_', because it is sits along side of __ptr and its natural index is 1.
		# but we have 2 sub elements under '__cntrl_' which we are indexing to a flat index structure, hence no '__cntrl_' value.
		# this doesn't work for the child items, thus we use GetChildAtIndex(3) to obtain '__cntrl_' when requried. 
		# see next function.
		return -1

	def get_child_at_index(self, index):
		if index == 0:
			return self.valobj.GetChildMemberWithName('__ptr_')
		if index == 1:
			return self.valobj.GetChildMemberWithName('__cntrl_').GetChildMemberWithName('__shared_owners_')
		if index == 2:
			return self.valobj.GetChildMemberWithName('__cntrl_').GetChildMemberWithName('__shared_weak_owners_')
		if index == 3:
			# since we don't have a get_child_index('__cntrl_') to return the correct index value of 1. 
			# i've overloaded the meaning of 3 to get '__cntrl_' when the deugger python formatter is querying the pointer for a summary.
			return self.valobj.GetChildMemberWithName('__cntrl_')
		return None


class stdmap_iterator_node:

	def _left_impl(self):
		return stdmap_iterator_node(
			self.node.GetChildMemberWithName("_Left"))

	def _right_impl(self):
		return stdmap_iterator_node(
			self.node.GetChildMemberWithName("_Right"))

	def _parent_impl(self):
		return stdmap_iterator_node(
			self.node.GetChildMemberWithName("_Parent"))

	def _value_impl(self):
		return self.node.GetValueAsUnsigned(0)

	def _sbvalue_impl(self):
		return self.node

	def _null_impl(self):
		return self.value == 0 or self.node.GetChildMemberWithName("_Isnil").GetValueAsUnsigned(0) == 1

	def __init__(self, node):
		self.node = node

	left = property(_left_impl, None)
	right = property(_right_impl, None)
	parent = property(_parent_impl, None)
	value = property(_value_impl, None)
	is_null = property(_null_impl, None)
	sbvalue = property(_sbvalue_impl, None)

class COFF_stdmap_iterator_node:

	def _left_impl(self):
		if DBG_LOG:
			logger >> "returning left: " + str(hex(self.node.GetValueAsUnsigned(0))) + "->" + str(hex(self.node.GetChildMemberWithName("__left_").GetValueAsUnsigned(0)))
		return COFF_stdmap_iterator_node(
			self.node.GetChildMemberWithName("__left_"))

	def _right_impl(self):
		if DBG_LOG:
			logger >> "returning right: " + str(hex(self.node.GetValueAsUnsigned(0))) + "->" + str(hex(self.node.GetChildMemberWithName("__right_").GetValueAsUnsigned(0)))
		return COFF_stdmap_iterator_node(
			self.node.GetChildMemberWithName("__right_"))

	def _parent_impl(self):
		# the parent loses the node type (it's just end_node) - is it safe to assume it's always the subclass?
		p = self.node.GetChildMemberWithName("__parent_")
		p = p.Cast(self.node.GetType());
		if DBG_LOG:
			logger >> "returning parent: " + str(hex(self.node.GetValueAsUnsigned(0))) + "[[" + str(self.node) + "]]->" + str(hex(self.node.GetChildMemberWithName("__parent_").GetValueAsUnsigned(0)))
		return COFF_stdmap_iterator_node(p)

	def _value_impl(self):
		return self.node.GetValueAsUnsigned(0)

	def _sbvalue_impl(self):
		return self.node

	def _null_impl(self):
		if DBG_LOG:
			logger >> "returning isnull: " + str(self.node.GetValueAsUnsigned(0) == 0)
		return self.node.GetValueAsUnsigned(0) == 0

	def __init__(self, node):
		self.node = node

	left = property(_left_impl, None)
	right = property(_right_impl, None)
	parent = property(_parent_impl, None)
	value = property(_value_impl, None)
	is_null = property(_null_impl, None)
	sbvalue = property(_sbvalue_impl, None)


class stdmap_iterator:

	def tree_min(self, x):
		steps = 0
		if x.is_null:
			return None
		while (not x.left.is_null):
			x = x.left
			steps += 1
			if steps > self.max_count:
				if DBG_LOG:
					logger >> "Returning None - we overflowed"
				return None
		return x

	def tree_max(self, x):
		if x.is_null:
			return None
		while (not x.right.is_null):
			x = x.right
		return x

	def tree_is_left_child(self, x):
		if x.is_null:
			return None
		return True if x.value == x.parent.left.value else False

	def increment_node(self, node):
		if node.is_null:
			return None
		if not node.right.is_null:
			return self.tree_min(node.right)
		steps = 0
		while (not self.tree_is_left_child(node)):
			steps += 1
			if steps > self.max_count:
				if DBG_LOG:
					logger >> "Returning None - we overflowed"
				return None
			node = node.parent
		return node.parent

	def __init__(self, node, max_count=0):
		# we convert the SBValue to an internal node object on entry
		self.node = stdmap_iterator_node(node)
		self.max_count = max_count

	def value(self):
		return self.node.sbvalue  # and return the SBValue back on exit

	def next(self):
		node = self.increment_node(self.node)
		if node is not None and node.sbvalue.IsValid() and not(node.is_null):
			self.node = node
			return self.value()
		else:
			return None

	def advance(self, N):
		if N < 0:
			return None
		if N == 0:
			return self.value()
		if N == 1:
			return self.next()
		while N > 0:
			if self.next() is None:
				return None
			N = N - 1
		return self.value()

class COFF_stdmap_iterator:

	def tree_min(self, x):
		steps = 0
		if x.is_null:
			return None
		while (not x.left.is_null):
			x = x.left
			steps += 1
			if steps > self.max_count:
				if DBG_LOG:
					logger >> "Returning None - we overflowed"
				return None
		return x

	def tree_max(self, x):
		if x.is_null:
			return None
		while (not x.right.is_null):
			x = x.right
		return x

	def tree_is_left_child(self, x):
		if x.is_null:
			return None
		return True if x.value == x.parent.left.value else False

	def increment_node(self, node):
		if node.is_null:
			return None
		if not node.right.is_null:
			return self.tree_min(node.right)
		steps = 0
		while (not self.tree_is_left_child(node)):
			steps += 1
			if steps > self.max_count:
				if DBG_LOG:
					logger >> "Returning None - we overflowed"
				return None
			node = node.parent
		return node.parent

	def __init__(self, node, max_count=0):
		# we convert the SBValue to an internal node object on entry
		self.node = COFF_stdmap_iterator_node(node)
		self.max_count = max_count

	def value(self):
		return self.node.sbvalue  # and return the SBValue back on exit

	def next(self):
		node = self.increment_node(self.node)
		if node is not None and node.sbvalue.IsValid() and not(node.is_null):
			self.node = node
			return self.value()
		else:
			return None

	def advance(self, N):
		if N < 0:
			return None
		if N == 0:
			return self.value()
		if N == 1:
			return self.next()
		while N > 0:
			if self.next() is None:
				return None
			N = N - 1
		return self.value()

class stdmap_SynthProvider:

	def __init__(self, valobj, dict):
		if DBG_LOG:
			logger >> "__init__ stdmap_SynthProvider for " + str(valobj.GetName())
		self.valobj = valobj
		self.pointer_size = self.valobj.GetProcess().GetAddressByteSize()
		p = self.valobj.GetValueForExpressionPath('_Mypair._Myval2._Myval2._Mysize')
		self.count = p.GetValueAsUnsigned()
		if DBG_LOG:
			logger >> "__init__ num_children, count =	" + str(self.count)

	def update(self):
		self.count = None
		try:
			# we will set this to True if we find out that discovering a node in the map takes more steps than the overall size of the RB tree
			# if this gets set to True, then we will merrily return None for
			# any child from that moment on
			self.garbage = False
			self.tree = self.valobj.GetChildMemberWithName('_Mypair').GetChildMemberWithName('_Myval2').GetChildMemberWithName('_Myval2')
			self.root_node = self.tree.GetChildMemberWithName('_Myhead').GetChildMemberWithName('_Left')
			# this data is either lazily-calculated, or cannot be inferred at this moment
			# we still need to mark it as None, meaning "please set me ASAP"
			self.data_type = None
			self.data_size = None
			self.skip_size = None
		except:
			pass
		return None

	def num_children(self):
		global _map_capping_size
		if self.count is None:
			self.count = self.num_children_impl()
			if self.count > _map_capping_size:
				self.count = _map_capping_size
		return self.count

	def num_children_impl(self):
		try:
			p = self.valobj.GetChildMemberWithName('_Mypair')
			p = p.GetChildMemberWithName('_Myval2').GetChildMemberWithName('_Myval2')
			p = p.GetChildMemberWithName('_Mysize')
			return p.GetValueAsUnsigned()
		except:
			return 0

	def has_children(self):
		return True

	def get_data_type(self):
		if self.data_type is None or self.data_size is None:
			if self.num_children() == 0:
				return False
			deref = self.root_node.Dereference()
			if not(deref.IsValid()):
				return False
			value = deref.GetChildMemberWithName('_Myval')
			if not(value.IsValid()):
				return False
			self.data_type = value.GetType()
			self.data_size = self.data_type.GetByteSize()
			self.skip_size = None
			return True
		else:
			return True

	def get_value_offset(self, node):
		if self.skip_size is None:
			node_type = node.GetType()
			fields_count = node_type.GetNumberOfFields()
			for i in range(fields_count):
				field = node_type.GetFieldAtIndex(i)
				if field.GetName() == '_Myval':
					self.skip_size = field.GetOffsetInBytes()
					break
		return (self.skip_size is not None)

	def get_child_index(self, name):
		if name == "_Mysize":
			return self.num_children()
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "Retrieving child " + str(index)
		if index < 0:
			return None
		if index >= self.num_children():
			try:
				count = self.num_children()
				endian = self.valobj.target.byte_order
				ptr_size = self.valobj.target.addr_size
				return self.valobj.CreateValueFromData("",\
					lldb.SBData.CreateDataFromUInt64Array(endian,ptr_size,[count]),\
					self.valobj.GetType().GetBasicType(lldb.eBasicTypeInt))
			except Exception as err:
				logger >> "stdmap_SynthProvider:get_child_at_index exception: " + str(err)
				return '<exception: ' + str(err) + '>'				  
		if self.garbage:
			if DBG_LOG:
				logger >> "Returning None since this tree is garbage"
			return None
		try:
			iterator = stdmap_iterator(self.root_node, max_count=self.num_children())
			# the debug info for libc++ std::map is such that __begin_node_ has a very nice and useful type
			# out of which we can grab the information we need - every other node has a less informative
			# type which omits all value information and only contains housekeeping information for the RB tree
			# hence, we need to know if we are at a node != 0, so that we can
			# still get at the data
			need_to_skip = (index > 0)
			current = iterator.advance(index)
			if current is None:
				if DBG_LOG:
					logger >> "Tree is garbage - returning None"
				self.garbage = True
				return None
			if self.get_data_type():
				if not(need_to_skip):
					current = current.Dereference()
					obj = current.GetChildMemberWithName('_Myval')
					obj_data = obj.GetData()
					# make sure we have a valid offset for the next items
					self.get_value_offset(current)
					# we do not return __value_ because then we would end up with a child named
					# __value_ instead of [0]
					return self.valobj.CreateValueFromData(
						'[' + str(index) + ']', obj_data, self.data_type)
				else:
					# FIXME we need to have accessed item 0 before accessing
					# any other item!
					if self.skip_size is None:
#						 logger >> "You asked for item > 0 before asking for item == 0, I will fetch 0 now then retry"
						if self.get_child_at_index(0):
							return self.get_child_at_index(index)
						else:
							if DBG_LOG:
								logger >> "item == 0 could not be found. sorry, nothing can be done here."
							return None
					return current.CreateChildAtOffset(
						'[' + str(index) + ']', self.skip_size, self.data_type)
			else:
				if DBG_LOG:
					logger >> "Unable to infer data-type - returning None (should mark tree as garbage here?)"
				return None
		except Exception as err:
			 logger >> "stdmap_SynthProvider:get_child_at_index exception: " + str(err)
			 return '<exception: ' + str(err) + '>'

def stdmap_SummaryProvider(valobj, dict):
	if DBG_LOG:
		 logger >> "stdmap_SummaryProvider for " + str(valobj.GetName())
	p = valobj.GetChildMemberWithName('_Mysize')
	return 'size=' + str(p.GetValueAsUnsigned())


class COFF_stdmap_SynthProvider:
# ~\include\x86_64-w64-mingw32\c++\v1\map
# ~\include\x86_64-w64-mingw32\c++\v1\__tree
	def __init__(self, valobj, dict):
		if DBG_LOG:
			logger >> "COFF_stdmap_SynthProvider, __init__: " + valobj.name;
			logger >> "Type arg = " + valobj.GetChildMemberWithName('__tree_').GetType().name
			logger >> "Template arg = " + valobj.GetType().GetTemplateArgumentType(0).name
		typeName = valobj.GetChildMemberWithName('__tree_').GetType().name;
		resArgIdx = len('std::__1::__tree<')
		templateArgName = ExtractTemplateArg(typeName, resArgIdx)
		templateArgName = '!' + templateArgName;
		if DBG_LOG:
			logger >> "templateArgName = " + templateArgName
		self.data_type = valobj.GetFrame().GetModule().FindFirstType(templateArgName)
		self.data_size = self.data_type.GetByteSize()
		if DBG_LOG:
			logger >> "templateArgType = " + str(self.data_type);
		self.valobj = valobj
		self.pointer_size = self.valobj.GetProcess().GetAddressByteSize()
		p = self.valobj.GetValueForExpressionPath('__tree_.__pair3_.__value_')
		self.count = p.GetValueAsUnsigned()
		if DBG_LOG:
			logger >> "__init__ num_children, count =	" + str(self.count)

	def update(self):
		self.count = None
		try:
			# we will set this to True if we find out that discovering a node in the map takes more steps than the overall size of the RB tree
			# if this gets set to True, then we will merrily return None for
			# any child from that moment on
			self.garbage = False
			self.tree = self.valobj.GetChildMemberWithName('__tree_').GetChildMemberWithName('__pair1_').GetChildMemberWithName('__value_').GetChildMemberWithName('__left_')
			beginNode = self.valobj.GetChildMemberWithName('__tree_').GetChildMemberWithName('__begin_node_') 
			# the begin_node is an end_node, we want the actual tree node, assume that's what the top of tree kind is
			self.root_node =  beginNode.Cast(self.tree.GetType())  
			self.skip_size = 32		# !!! 
		except:
			pass
		return None

	def num_children(self):
		global _map_capping_size
		if self.count is None:
			self.count = self.num_children_impl()
			if self.count > _map_capping_size:
				self.count = _map_capping_size
		return self.count

	def num_children_impl(self):
		try:
			p = self.valobj.GetChildMemberWithName('__tree_')
			p = p.GetChildMemberWithName('__pair3_')
			p = p.GetChildMemberWithName('__value_')
			return p.GetValueAsUnsigned()
		except:
			return 0

	def has_children(self):
		return True

	def get_data_type(self):
		if self.data_type is None or self.data_size is None:
			if self.num_children() == 0:
				return False
			deref = self.root_node.Dereference()
			if not(deref.IsValid()):
				return False
			value = deref.GetChildMemberWithName('_Myval')
			if not(value.IsValid()):
				return False
			self.data_type = value.GetType()
			self.data_size = self.data_type.GetByteSize()
			self.skip_size = None
			return True
		else:
			return True

	def get_value_offset(self, node):
		if self.skip_size is None:
			node_type = node.GetType()
			fields_count = node_type.GetNumberOfFields()
			for i in range(fields_count):
				field = node_type.GetFieldAtIndex(i)
				if field.GetName() == '_Myval':
					self.skip_size = field.GetOffsetInBytes()
					break
		return (self.skip_size is not None)

	def get_child_index(self, name):
		if name == "_Mysize":
			return self.num_children()
		try:
			return int(name.lstrip('[').rstrip(']'))
		except:
			return -1

	def get_child_at_index(self, index):
		if DBG_LOG:
			logger >> "Retrieving child " + str(index)
		if index < 0:
			return None
		if index >= self.num_children():
			try:
				count = self.num_children()
				endian = self.valobj.target.byte_order
				ptr_size = self.valobj.target.addr_size
				rv = self.valobj.CreateValueFromData("",\
					lldb.SBData.CreateDataFromUInt64Array(endian,ptr_size,[count]),\
					self.valobj.GetType().GetBasicType(lldb.eBasicTypeInt))
				if DBG_LOG:
					logger >> "map rv: " + str(rv)
				return rv
			except Exception as err:
				logger >> "Hit an exception: " + str(err)
				return '<exception: ' + str(err) + '>'				  
		if self.garbage:
			if DBG_LOG:
				logger >> "Returning None since this tree is garbage"
			return None
		try:
			iterator = COFF_stdmap_iterator(self.root_node, max_count=self.num_children())
			if DBG_LOG:
				logger >> "iterator is: "
				logger >> str(iterator.node.node)
			current = iterator.advance(index)
			if current is None:
				if DBG_LOG:
					logger >> "current is garbage - returning None"
				self.garbage = True
				return None
			if self.get_data_type():
				nm = '[' + str(index) + ']'
				if DBG_LOG:
					logger >> "current is: " + str(current)
				Ptr = current
				if DBG_LOG:
					logger >> "Ptr is: " + str(Ptr)
				# this causes a character encoding exception on wide chars
				#Ptr = Ptr.Cast(self.valobj.GetType().GetBasicType(lldb.eBasicTypeChar).GetPointerType())
				elem = self.valobj.CreateValueFromAddress(nm, Ptr.GetValueAsUnsigned() + self.skip_size, self.data_type)
				# COFF maps encapsulate the key/value pairs in __cc.first/second members
				# so we get the '__cc' object
				cc = elem.GetChildMemberWithName('__cc')
				# then convert that to a SBValue for the debugger, later the first/second members will be renamed to key/value
				# using the COFF_MapPair_SynthProvider class
				elem = self.valobj.CreateValueFromData(nm, cc.GetData(), cc.GetType())
				if DBG_LOG:
					logger >> "elem: " + str(elem)
				return elem
			else:
				if DBG_LOG:
					logger >> "Unable to infer data-type - returning None (should mark tree as garbage here?)"
				return None
		except Exception as err:
			logger >> "Hit an exception: " + str(err)
			return '<exception: ' + str(err) + '>'

# this sythentic is used to change the view of a std::map pair.
# changing first/second to key/value
class COFF_MapPair_SynthProvider:
	def __init__(self, valobj, dict):
		if DBG_LOG:
			logger >> "COFF_map_pair_SynthProvider for " + str(valobj.GetName())
		self.valobj = valobj
		
	def update(self):
		return False
	
	def has_children(self):
		return True

	def num_children(self):
		return 2
		
	def get_child_index(self,name):
		if DBG_LOG:
			logger >> "COFF_map_pair_SynthProvider:get_child_index " + name
		if name == "first":
			return 0
		if name == "second":
			return 1
		return -1

	def get_child_at_index(self,index):
		if DBG_LOG:
			logger >> "COFF_map_pair_SynthProvider:get_child_at_index " + str(index)
		try:
			rv = self.valobj.GetChildAtIndex(index)
			if index == 0:
				rv = self.valobj.CreateValueFromData("key", rv.GetData(), rv.GetType())
			if index == 1:
				rv = self.valobj.CreateValueFromData("value", rv.GetData(), rv.GetType())
			if DBG_LOG:
				logger >> str(rv)
			return rv
		except Exception as err:
			if DBG_LOG:
				logger >> "Hit an exception: " + str(err)
			return '<exception: ' + str(err) + '>'

def __lldb_init_module(debugger, dict):
	if DBG_LOG:
		lldb.formatters.Logger._lldb_formatters_debug_level = 3
		lldb.formatters.Logger._lldb_formatters_debug_filename = "d:\\formatter_log.log"
		global logger
		logger = lldb.formatters.Logger.Logger()
		logger >> "Starting: __lldb_init_module"
	
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_StdList_SynthProvider -x "^std::__1::list<.+>(( )?&)?$" --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.generic_pointer_SummaryProvider "void *"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.generic_pointer_SummaryProvider -x "system(::|\\.)tobject *"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.generic_pointer_SummaryProvider -x "System(::|\\.)TObject *"  --category EMBT_FMT')
#	debugger.HandleCommand('type summary add -F embt_formatters.systdatetime_SummaryProvider -x "(S|s)ystem((::)|\\.)(TD|td)ate(T|t)ime"  --category EMBT_FMT')
#	debugger.HandleCommand('type summary add -F embt_formatters.systdatetime_SummaryProvider -x "(S|s)ystem((::)|\\.)(TD|td)ate"  --category EMBT_FMT')
#	debugger.HandleCommand('type summary add -F embt_formatters.systdatetime_SummaryProvider -x "(S|s)ystem((::)|\\.)(T|t)ime"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.syscurrency_SummaryProvider -x "(S|s)ystem(::|\\.)Currency"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.stdstring_SummaryProvider "std::string"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.DelphiString_SummaryProvider "DelphiString"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.DelphiDynArray_SynthProvider -x "^__lldb_DDA_[^[]*( )*$"  --category EMBT_FMT')
#
	debugger.HandleCommand('type summary add -F embt_formatters.DelphiSet_SummaryProvider -x "^.*__lldb_SET_[^[]*( )*$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stdstring_SummaryProvider "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stdwstring_SummaryProvider "std::__1::basic_string<wchar_t, std::__1::char_traits<wchar_t>, std::__1::allocator<wchar_t>>"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.shortstring_SummaryProvider "System::SmallStringBase<(unsigned char)255>"  --category EMBT_FMT')
#
	debugger.HandleCommand('type summary add -F embt_formatters.stdstring_SummaryProvider "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stdstring_SummaryProvider "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.stdwstring_SummaryProvider "std::wstring"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.ansistringT_SummaryProvider -x "^System::AnsiStringT<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.ansistring_SummaryProvider "System::AnsiString"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.unicodestring_SummaryProvider "System::UnicodeString"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.shortstring_SummaryProvider "System::ShortString"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.widestring_SummaryProvider "System::WideString"  --category EMBT_FMT')
	# fixed
	debugger.HandleCommand('type synthetic add -l embt_formatters.stdsharedptr_SynthProvider -x "^std::shared_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.stdsharedptr_SummaryProvider -x "^std::shared_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	# fixed
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_stdsharedptr_SynthProvider -x "^std::__1::shared_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stdsharedptr_SummaryProvider -x "^std::__1::shared_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	# fixed
	debugger.HandleCommand('type synthetic add -l embt_formatters.stduniqueptr_SynthProvider -x "^std::unique_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.stduniqueptr_SummaryProvider -x "^std::unique_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	# fixed
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_stduniqueptr_SynthProvider -x "^std::__1::unique_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	# fixed
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stduniqueptr_SummaryProvider -x "^std::__1::unique_ptr<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.StdVector_SynthProvider -x "^std::vector<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_StdVector_SynthProvider -x "^std::__1::vector<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.stddeque_SynthProvider -x "^std::deque<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_stddeque_SynthProvider -x "^std::__1::deque<.+>(( )?&)?$"  --category EMBT_FMT')
#	debugger.HandleCommand('type summary add -F embt_formatters.stddeque_SummaryProvider ^std::deque<.+>(( )?&)?$"  --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.stdmap_SynthProvider -x "^std::map<.+> >$"  --category EMBT_FMT')
	debugger.HandleCommand('type summary add -F embt_formatters.stdmap_SummaryProvider -e -x "^std::map<.+> >$"  --category EMBT_FMT')
	# fixed/improved
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_stdmap_SynthProvider -x "^std::__1::map<.+>(( )?&)?$"  --category EMBT_FMT')
	# fixed/improved
	debugger.HandleCommand('type summary add -F embt_formatters.COFF_stdmap_SummaryProvider -e -x "^std::__1::map<.+>(( )?&)?$"  --category EMBT_FMT')
	# new map pair summary
	debugger.HandleCommand('type summary add --summary-string "key=${var.first}" -e -x "^std::__1::pair<.+>(( )?&)?$" --category EMBT_FMT')
	# new map pair synthetic
	debugger.HandleCommand('type synthetic add -l embt_formatters.COFF_MapPair_SynthProvider -x "^std::__1::pair<.+>(( )?&)?$" --category EMBT_FMT')
	debugger.HandleCommand('type synthetic add -l embt_formatters.syststringlist_SynthProvider -x "System::Classes::TStringList"  --category EMBT_FMT')

_map_capping_size = 255